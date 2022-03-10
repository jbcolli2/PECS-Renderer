//
// Created by Jeb Collins on 3/7/22.
//

#ifndef PECS_RENDERER_RENDERPIPELINE_HPP
#define PECS_RENDERER_RENDERPIPELINE_HPP

#include "Components/Renderable.hpp"
#include "Systems/System.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Window.hpp"

namespace pecs
{

class RenderPipeline : public System
{
private:
    // Path to folder with shaders
    const std::string SHADER_FOLDER = "../shaders/";
    const std::string BASICVERT_PATH = SHADER_FOLDER + "PosNormUVVert.glsl";
    const std::string SOLIDFRAG_PATH = SHADER_FOLDER + "SolidColorFrag.glsl";

    // ************* Shaders  **************************** //
    Shader m_solidShader{};

    // ************* UBO  **************************** //
    unsigned int m_uboVP;
    glm::mat4 m_view{1.f}, m_proj{1.f};
public:
    /***************** RenderPipeline::SetupPipeline  ******************
     * @brief 1. Create shader programs
     *        2. Setup any framebuffers and empty textures for the framebuffers
     *        3. For any deferred rendering, setup the VAO/VBO for screen quad
    ***************************************///
    void SetupPipeline();

    /***************** RenderPipeline::SetupShape  ******************
     * @brief Only used if renderType is not Model.
     *
     *      1. Use the type of the Renderable component to fill the vertices vector with
     *      a standard version of the given shape.
     *      2. Create VAO/VBO.
     *      3. Load all textures and create TBO.
    ***************************************************///
    void SetupShape();


    /***************** RenderPipeline::SetupModel  ******************
     * @brief Only used if renderType is Model
     *
     *      1. Use the .obj file to fill the vertices vector.
     *      2. Create VAO/VBO.
     *      3. Load all textures and create TBO.
    ******************************************************************///
    void SetupModel();


    /***************** RenderPipeline::Update  ******************
     * @brief Draw all objects associated with the pipeline.
    ***************************************///
    void Update();



private:
    /***************** genVertexData  ******************
     * @brief Fills all the vertex data of a Renderable with the appropriate verts given
     *      the renderType
     *
     * @param renderableObj The Renderable compoenent of an object.
    ******************************************************************/
    static void genVertexData(const std::shared_ptr<Renderable>& renderableObj);


    /***************** fillVertsWithCube/Plane  ******************
     * @brief First clears the passed vector and then fills the passed vector with vertex information
     *      of the shape.  The vertex attributes are Pos/Norm/UV
     *
     *      - For a cube: dimensiona are [-1,1]^3
     *      - For a plane: [-1,-1]^2 at y=0.
     *
     * @param vertsVector Vector in which to add the cube vertex info.
    ******************************************************************/
    static void fillVertsWithCube(std::vector<Vert3x3x2f>& vertsVector);
    static void fillVertsWithPlane(std::vector<Vert3x3x2f>& vertsVector);
};  // End class RenderPipeline


} // end namespace pecs

#endif //PECS_RENDERER_RENDERPIPELINE_HPP
