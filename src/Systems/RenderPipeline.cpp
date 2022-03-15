//
// Created by Jeb Collins on 3/7/22.
//

#include "RenderPipeline.hpp"

using namespace pecs;



/***************** RenderPipeline::SetupPipeline  ******************
 * @brief 1. Create shader programs
 *        2. Setup any framebuffers and empty textures for the framebuffers
 *        3. For any deferred rendering, setup the VAO/VBO for screen quad
 *        4. Setup and UBOs
***************************************///
void RenderPipeline::SetupPipeline()
{
    // ************* Split up objects  **************************** //
    for(auto obj : m_objects)
    {
        if(HasComponent<Renderable>(obj))
        {
            m_renderables.emplace_back(obj);
        }
        if(HasComponent<Light>(obj))
        {
            m_lights.emplace_back(obj);
        }
        if (HasComponent<Camera>(obj))
        {
            m_cameras.emplace_back(obj);
        }
    }


    // ************* Shaders  **************************** //
    m_lightShader = Shader(BASICVERT_PATH, LIGHTFRAG_PATH);

    // ************* Uniform Buffer Objects  **************************** //
    glGenBuffers(1, &m_uboVP);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboVP);
    glBufferData(GL_UNIFORM_BUFFER, 16*8, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uboVP);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    
    // ************* Setup Uniforms in shaders  **************************** //
    m_lightShader.startProgram();
    setupLightUniforms(m_lightShader);
    m_lightShader.stopProgram();
}




/***************** RenderPipeline::SetupShape  ******************
 * @brief Only used if renderType is not Model.
 *
 *      1. Use the type of the Renderable component to fill the vertices vector with
 *      a standard version of the given shape.
 *      2. Create VAO/VBO.
 *      3. Load all textures and create TBO.
***************************************************///
void RenderPipeline::SetupShape()
{
    std::shared_ptr<Renderable> shape{};

    for(auto obj : m_objects)
    {
        shape = obj->GetComponent<Renderable>();
        if(shape == nullptr)
            continue;
        // if obj has Renderable component
        genVertexData(shape);
    }
}


/***************** setupLightUniforms  ******************
 * @brief Set all the light uniforms that don't change per frame such as diffuse
 *       and the attenuation data.
******************************************************************/
void RenderPipeline::setupLightUniforms(Shader& shader)
{
    std::shared_ptr<Light> lightComp{nullptr};
    std::string lightName{""};
    for(const auto& light : m_lights)
    {
        lightComp = light->GetComponent<Light>();
        if(HasComponent<DirLight>(light))
        {
            lightName = DirLight::name + ".";
        }
        // TODO: Add option for point light.  Can have multiple point lights, so be sure to also
        //  include the subscript in the lightName for point lights
        
        
        shader.setUniform3f(lightName + "diffuse", lightComp->diffuse.r, lightComp->diffuse.g, lightComp->diffuse.b);
        shader.setUniform3f(lightName + "specular", lightComp->specular.r, lightComp->specular.g, lightComp->specular.b);
        shader.setUniform1f(lightName + "ambientFactor", lightComp->ambientFactor);

        shader.setUniform1f(lightName + "attenConst", lightComp->attenConst);
        shader.setUniform1f(lightName + "attenLin", lightComp->attenLin);
        shader.setUniform1f(lightName + "attenQuad", lightComp->attenQuad);
    }
}







/*********************************************************************************************************/


/***************** RenderPipeline::Update  ******************
 * @brief 1. Update shader uniforms for variables that can change
 *      2. Render all objects.
***************************************///
void RenderPipeline::Render()
{
    // Set OpenGL state to default
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: View and Projection matrices are being hardcoded right now.
    m_view = glm::lookAt(glm::vec3(-2.f, 1.5f, 5.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
    m_proj = glm::perspective(glm::radians(45.f), Window::aspectRatio, .1f, 100.f);

    // Fill UBO with view and proj matrices
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboVP);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_view));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_proj));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Start shader and set the uniforms
    m_lightShader.startProgram();
    glm::mat4 model = glm::mat4(1.f);
    m_lightShader.setUniformMatrix4f("model", model);

    updateLightUniforms(m_lightShader);

    // Draw all objects with solid shader
    std::shared_ptr<Renderable> renderData;
    for(auto obj : m_renderables)
    {
        renderData = obj->GetComponent<Renderable>();
        glBindVertexArray(renderData->vao);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(renderData->vertices.size()) );
    }
    glBindVertexArray(0);


    m_lightShader.stopProgram();
}














/***************** fillVertexData  ******************
 * @brief Fills all the vertex data of a Renderable with the appropriate verts given
 *      the renderType.
******************************************************************/
void RenderPipeline::genVertexData(const std::shared_ptr<Renderable>& renderableObj)
{
    switch(renderableObj->renderType)
    {
        case RenderType::Cube:
            fillVertsWithCube(renderableObj->vertices);
            break;
        case RenderType::Plane:
            fillVertsWithPlane(renderableObj->vertices);
            break;
        default:
            break;
    }

    glGenVertexArrays(1, &renderableObj->vao);
    glBindVertexArray(renderableObj->vao);
    renderableObj->vbo = loadVBOData(renderableObj->vertices);
    glBindVertexArray(0);
}


/***************** fillVertsWithCube  ******************
 * @brief First clears the passed vector and then fills the passed vector with vertex information
 *      of a cube from [-1,1]^3.  Vertex attribues are Pos/Norm/UV.
******************************************************************/
void RenderPipeline::fillVertsWithCube(std::vector<Vert3x3x2f>& vertsVector)
{
    vertsVector.clear();

    // front
    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, 1.f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, 1.f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, 1.f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));

    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, 1.f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, 1.f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, 1.f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));

    //back
    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, -1.f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, -1.f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, -1.f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, -1.f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, -1.f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, -1.f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));

    //top
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, 1.f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, 1.f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, -1.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));

    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, 1.f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, -1.f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, -1.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));

    // bottom
    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, 1.f, 0.0f, -1.0f, 0.0f, 0.0f, 0.f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, -1.f, 0.0f, -1.0f, 0.0f, 0.0f, 1.f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, 1.f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f));

    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, 1.f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, -1.f, 0.0f, -1.0f, 0.0f, 0.0f, 1.f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, -1.f, 0.0f, -1.0f, 0.0f, 1.0f, 1.f));

    //right
    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, 1.f, 1.0f, 0.0f, 0.0f, 0.0f, 0.f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, -1.f, 1.0f, 0.0f, 0.0f, 1.0f, 0.f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, 1.f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));

    vertsVector.emplace_back(Vert3x3x2f(1.f, -1.f, -1.f, 1.0f, 0.0f, 0.0f, 1.0f, 0.f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, -1.f, 1.0f, 0.0f, 0.0f, 1.0f, 1.f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 1.f, 1.f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));

    // left
    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, 1.f, -1.0f, 0.0f, 0.0f, 0.0f, 0.f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, 1.f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, -1.f, -1.0f, 0.0f, 0.0f, 1.0f, 0.f));

    vertsVector.emplace_back(Vert3x3x2f(-1.f, -1.f, -1.f, -1.0f, 0.0f, 0.0f, 1.0f, 0.f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, 1.f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 1.f, -1.f, -1.0f, 0.0f, 0.0f, 1.0f, 1.f));
} // End fill cube verts



void RenderPipeline::fillVertsWithPlane(std::vector<Vert3x3x2f>& vertsVector)
{
    vertsVector.clear();

    // front
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 0.0f, 1.f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 0.0f, 1.f, 0.0f, 1.0f, 0.0f, 1.f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 0.0f, -1.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.f));

    vertsVector.emplace_back(Vert3x3x2f(1.f, 0.0f, 1.f, 0.0f, 1.0f, 0.0f, 1.f, 0.0f));
    vertsVector.emplace_back(Vert3x3x2f(1.f, 0.0f, -1.f, 0.0f, 1.0f, 0.0f, 1.f, 1.f));
    vertsVector.emplace_back(Vert3x3x2f(-1.f, 0.0f, -1.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.f));
} // End fill plane verts





/***************** updateLightUniforms  ******************
 * @brief Set all the light uniforms that change per frame.  Assume shader program is already
 *      being used.
******************************************************************/
void RenderPipeline::updateLightUniforms(Shader &shader)
{
    std::shared_ptr<DirLight> dirLightComp{nullptr};
    for(const auto& light : m_lights)
    {
        if(HasComponent<DirLight>(light))
        {
            dirLightComp = light->GetComponent<DirLight>();

            shader.setUniform3f(DirLight::name + ".direction", dirLightComp->direction.x, dirLightComp->direction.y,
                                dirLightComp->direction.z);
        }
    }
}













