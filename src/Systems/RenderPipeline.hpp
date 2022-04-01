//
// Created by Jeb Collins on 3/7/22.
//

#ifndef PECS_RENDERER_RENDERPIPELINE_HPP
#define PECS_RENDERER_RENDERPIPELINE_HPP

#include "Components/Renderable.hpp"
#include "Components/Light.hpp"
#include "Components/Camera.hpp"

#include "Systems/System.hpp"

#include "Engine/Shader.hpp"
#include "Engine/Window.hpp"

namespace pecs
{

class RenderPipeline : public System
{
private:
    // Path to folder with shaders
    const std::string VERTSHADER_FOLDER = "../shaders/VertexShaders/";
    const std::string FRAGSHADER_FOLDER = "../shaders/FragmentShaders/";
    const std::string BASICVERT_PATH = VERTSHADER_FOLDER + "PosNormUVVert.glsl";
    const std::string SOLIDFRAG_PATH = FRAGSHADER_FOLDER + "SolidColorFrag.glsl";
    const std::string LIGHTFRAG_PATH = FRAGSHADER_FOLDER + "LightFrag.glsl";


    // List of renderable objects
    std::vector<Object*> m_renderables{};
    // List of Light objects
    std::vector<Object*> m_lights{};
    // List of Camera objects
    std::vector<Object*> m_cameras{};

    // ************* Shaders  **************************** //
    Shader m_solidShader{};
    Shader m_lightShader{};

    // ************* Fulstrum variables  **************************** //
    float m_nearField{.1f};
    float m_farField{100.f};

    // ************* UBO  **************************** //
    unsigned int m_uboVP;
    glm::mat4 m_view{1.f}, m_proj{1.f};
public:
    /***************** RenderPipeline::SetupPipeline  ******************
     * @brief - Create shader programs
     *        - Split up objects into three categories, renderables, lights, and cameras
     *        - Setup any framebuffers and empty textures for the framebuffers
     *        - For any deferred rendering, setup the VAO/VBO for screen quad
    ***************************************///
    void SetupPipeline();

    //***************** RenderPipeline::SetupShape  ******************/
    /**
     * @brief Only used if \p renderType is not Model.
     *
     *      1. Use the type of the Renderable component to fill the vertices vector with
     *      a standard version of the given shape.
     *      2. Create VAO/VBO.
     *      3. Load all textures and create TBO.
    ***************************************************/
    void SetupShape();


    /***************** RenderPipeline::SetupModel  ******************
     * @brief Only used if renderType is Model
     *
     *      1. Use the .obj file to fill the vertices vector.
     *      2. Create VAO/VBO.
     *      3. Load all textures and create TBO.
    ******************************************************************///
    void SetupModel();


    /***********************************************************************************************/

    /***************** RenderPipeline::Render  ******************
     * @brief Draw all objects associated with the pipeline.
    ***************************************///
    void Render();



private:
    /***************** genVertexData  ******************
     * @brief Fills all the vertex data of a Renderable with the appropriate verts given
     *      the renderType
     *
     * @param renderableObj The Renderable component of an object.
    ******************************************************************/
    static void genVertexData(const std::shared_ptr<Renderable>& renderableObj);


    /***************** setupLightUniforms  ******************
     * @brief Set all the light uniforms that don't change per frame such as diffuse
     *       and the attenuation data
     *
     * @param shader Shader to set the uniforms.
    ******************************************************************/
    void setupLightUniforms(Shader& shader);


    /***************** fillVertsWithCube/Plane  ******************
     * @brief First clears the passed vector and then fills the passed vector with vertex information
     *      of the shape.  The vertex attributes are Pos/Norm/UV
     *
     *      - For a cube: dimensions are [-1,1]^3
     *      - For a plane: [-1,-1]^2 at y=0.
     *
     * @param vertsVector Vector in which to add the cube vertex info.
    ******************************************************************/
    static void fillVertsWithCube(std::vector<Vert3x3x2f>& vertsVector);
    static void fillVertsWithPlane(std::vector<Vert3x3x2f>& vertsVector);



    /*****************************************************************************************************/

    /***************** updateLightUniforms  ******************
     * @brief Set all the light uniforms that change per frame.  Assume shader program is already
     *      being used.
     *
     * @param shader Shader in which to update the uniforms.
    ******************************************************************/
    void updateLightUniforms(Shader& shader);
};  // End class RenderPipeline


} // end namespace pecs

#endif //PECS_RENDERER_RENDERPIPELINE_HPP
