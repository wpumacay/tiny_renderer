
#include <CEngine.h>

engine::CRenderOptions g_renderOptions;

engine::CVec3 g_lightDirPosition    = { 0.0f, 10.0f, 0.0f };
engine::CVec3 g_lightPointPosition  = { 0.0f, 10.0f, 0.0f };
engine::CVec3 g_lightSpotPosition   = { 0.0f, 10.0f, 0.0f };

// engine::CVec3 g_lightDirPosition    = { -2.0f, 4.0f, -1.0f };
// engine::CVec3 g_lightPointPosition  = { -2.0f, 4.0f, -1.0f };
// engine::CVec3 g_lightSpotPosition   = { -2.0f, 4.0f, -1.0f };

engine::CVec3 g_lightDirDirection   = engine::CVec3::normalize( -g_lightDirPosition );
engine::CVec3 g_lightPointDirection = engine::CVec3::normalize( -g_lightPointPosition );
engine::CVec3 g_lightSpotDirection  = engine::CVec3::normalize( -g_lightSpotPosition );

engine::CVec3 g_focusPoint = { 0.0f, 0.0f, 0.0f };
const engine::CVec3 g_worldUp = { 0.0f, 1.0f, 0.0f };

bool g_useAutofixToCamera = false;

float g_widthDir = 20.0f;
float g_heightDir = 20.0f;
float g_depthDir = 10.0f;

float g_znearPoint = 0.1f;
float g_zfarPoint = 15.0f;
float g_fovPoint = 120.0f;

float g_znearSpot = 0.1f;
float g_zfarSpot = 15.0f;
float g_fovSpot = 120.0f;

float g_extraWidth = 1.0f;
float g_extraHeight = 1.0f;
float g_extraDepth = 1.0f;

class ApplicationUi : public engine::CImguiUi
{

public :

    ApplicationUi( engine::COpenGLContext* context ) 
        : engine::CImguiUi( context ) 
    {
        
    }

    ~ApplicationUi() {}

    void setRenderer( engine::CMainRenderer* rendererPtr )
    {
        m_rendererPtr = rendererPtr;
    }

    void setMeshRenderer( engine::CMeshRenderer* meshRendererPtr )
    {
        m_meshRendererPtr = meshRendererPtr;
    }

    engine::CILight* selectedLight() const { return m_lights[m_lightSelectedIndex]; }

protected :

    void _initInternal() override
    {
        m_rendererPtr = nullptr;
        m_meshRendererPtr = nullptr;

        auto _dirlight = new engine::CDirectionalLight( "directional",
                                                        { 0.2f, 0.2f, 0.2f },
                                                        { 0.4f, 0.4f, 0.4f },
                                                        { 0.8f, 0.8f, 0.8f },
                                                        g_lightDirDirection );

        auto _pointlight = new engine::CPointLight( "point",
                                                    { 0.2f, 0.2f, 0.2f },
                                                    { 0.5f, 0.5f, 0.5f },
                                                    { 0.8f, 0.8f, 0.8f },
                                                    g_lightPointPosition,
                                                    1.0f, 0.05f, 0.005f );

        auto _spotLight = new engine::CSpotLight( "spot",
                                                  { 0.2f, 0.2f, 0.2f },
                                                  { 0.5f, 0.5f, 0.5f },
                                                  { 0.8f, 0.8f, 0.8f },
                                                  g_lightSpotPosition,
                                                  g_lightSpotDirection,
                                                  1.0f, 0.05f, 0.005f,
                                                  ENGINE_PI / 4.0f,
                                                  ENGINE_PI / 3.0f );

        m_lights = { _dirlight, _pointlight, _spotLight };
        m_lightsNames = { "directional", "point", "spot" };
        m_lightSelectedIndex = 2;
        m_lightSelectedName = m_lightsNames[m_lightSelectedIndex];

        m_lightDirDirection     = g_lightDirDirection;
        m_lightPointDirection   = g_lightPointDirection;
        m_lightSpotDirection    = g_lightSpotDirection;

        m_lightPointPosition    = g_lightPointPosition;
        m_lightSpotPosition     = g_lightSpotPosition;
    }

    void _renderInternal() override
    {
        _menuUiRendererStats();
        _menuUiLights();
        _menuUiRendererFrustumCulling();
        _menuUiRendererShadowMap();
    }

private :

    void _menuUiRendererStats()
    {
        ImGui::Begin( "statistics" );
        ImGui::Text( "fps           : %.5f", engine::COpenGLApp::GetInstance()->fps() );
        ImGui::Text( "frame-time    : %.5f", engine::COpenGLApp::GetInstance()->frametime() );
        ImGui::End();
    }

    void _menuUiRendererFrustumCulling()
    {
        if ( !m_rendererPtr )
            return;

        ImGui::Begin( "frustum-culling" );

        ImGui::Checkbox( "use-frustum-culling", &g_renderOptions.useFrustumCulling );
        if ( g_renderOptions.useFrustumCulling )
        {
            int _cullingGeomOption = ( g_renderOptions.cullingGeom == engine::eCullingGeom::BOUNDING_BOX ) ? 0 : 1;
            ImGui::RadioButton( "Box", &_cullingGeomOption, 0 );
            ImGui::SameLine();
            ImGui::RadioButton( "Sphere", &_cullingGeomOption, 1 );
            g_renderOptions.cullingGeom = ( _cullingGeomOption == 0 ) ? engine::eCullingGeom::BOUNDING_BOX : engine::eCullingGeom::BOUNDING_SPHERE;
        }

        ImGui::Spacing();
        ImGui::Text( m_rendererPtr->status().c_str() );
        ImGui::End();
    }

    void _menuUiRendererShadowMap()
    {
        if ( !m_rendererPtr )
            return;

        // grab depth-map texture from shadowmap
        auto _depthMapTexture = m_rendererPtr->shadowMap()->frameBuffer()->getTextureAttachment( "shadow_depth_attachment" );

        if ( !_depthMapTexture )
            return;

        ImGui::Begin( "shadow-map" );

        ImGui::Image( (void*)(intptr_t) _depthMapTexture->openglId(),
                      ImVec2( 200.0, 200.0 ),
                      ImVec2( 0.0, 0.0 ), ImVec2( 1.0, 1.0 ) );

        ImGui::End();
    }

    void _menuUiLights()
    {
        ImGui::Begin( "Lights" );

        ImGui::Spacing();

        if ( ImGui::BeginCombo( "Lights", m_lightSelectedName.c_str() ) )
        {
            for ( size_t i = 0; i < m_lights.size(); i++ )
            {
                std::string _lightName = m_lightsNames[i];
                bool _isSelected = ( _lightName == m_lightSelectedName );

                if ( ImGui::Selectable( _lightName.c_str(), _isSelected ) )
                {
                    m_lightSelectedName = _lightName;
                    m_lightSelectedIndex = i;
                }

                if ( _isSelected )
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        ImGui::Spacing();

        _menuUiLightShadowProps();

        ImGui::Spacing();
        ImGui::Text( m_lights[ m_lightSelectedIndex ]->toString().c_str() );
        ImGui::End();
    }

    void _menuUiLightShadowProps()
    {
        auto _lightPtr = m_lights[m_lightSelectedIndex];
        if ( _lightPtr->type() == engine::eLightType::DIRECTIONAL )
        {
            /* shadow frustum transform in world-space (view) */
            float _direction[3] = { m_lightDirDirection.x, m_lightDirDirection.y, m_lightDirDirection.z };
            ImGui::SliderFloat3( "direction", _direction, -10.0f, 10.0f );
            m_lightDirDirection = { _direction[0], _direction[1], _direction[2] };

            g_lightDirDirection = engine::CVec3::normalize( m_lightDirDirection );
            _lightPtr->direction = g_lightDirDirection;

            // whether or not to use autofix-to-camera for directional lights shadowmapping
            ImGui::Checkbox( "autofix-to-camera", &g_useAutofixToCamera );

            /* shadow-frustum size properties (proj) */
            if ( g_useAutofixToCamera )
            {
                ImGui::SliderFloat( "extra-width", &g_extraWidth, 0.0f, 5.0f );
                ImGui::SliderFloat( "extra-height", &g_extraHeight, 0.0f, 5.0f );
                ImGui::SliderFloat( "extra-depth", &g_extraDepth, 0.0f, 5.0f );
            }
            else
            {
                ImGui::SliderFloat( "depth", &g_depthDir, 0.1f, 20.0f );
                ImGui::SliderFloat( "width", &g_widthDir, 20.0f, 40.0f );
                ImGui::SliderFloat( "height", &g_heightDir, 20.0f, 40.0f );

                float _focusp[3] = { g_focusPoint.x, g_focusPoint.y, g_focusPoint.z };
                ImGui::SliderFloat3( "focus", _focusp, -10.0f, 10.0f );
                g_focusPoint = { _focusp[0], _focusp[1], _focusp[2] };
            }
        }
        else if ( _lightPtr->type() == engine::eLightType::POINT )
        {
            float _position[3] = { m_lightPointPosition.x, m_lightPointPosition.y, m_lightPointPosition.z };
            ImGui::SliderFloat3( "position", _position, -10.0f, 10.0f );
            m_lightPointPosition = { _position[0], _position[1], _position[2] };

            g_lightPointDirection = engine::CVec3::normalize( m_lightPointDirection );
            g_lightPointPosition = m_lightPointPosition;
            _lightPtr->position = g_lightPointPosition;

            ImGui::SliderFloat( "znear", &g_znearPoint, 0.1f, 5.0f );
            ImGui::SliderFloat( "zfar", &g_zfarPoint, g_znearPoint, 20.0f );
            ImGui::SliderFloat( "fov", &g_fovPoint, 20.0f, 150.0f );

            float _focusp[3] = { g_focusPoint.x, g_focusPoint.y, g_focusPoint.z };
            ImGui::SliderFloat3( "focus", _focusp, -10.0f, 10.0f );
            g_focusPoint = { _focusp[0], _focusp[1], _focusp[2] };
        }
        else if ( _lightPtr->type() == engine::eLightType::SPOT )
        {
            float _direction[3] = { m_lightSpotDirection.x, m_lightSpotDirection.y, m_lightSpotDirection.z };
            ImGui::SliderFloat3( "direction", _direction, -10.0f, 10.0f );
            m_lightSpotDirection = { _direction[0], _direction[1], _direction[2] };

            float _position[3] = { m_lightSpotPosition.x, m_lightSpotPosition.y, m_lightSpotPosition.z };
            ImGui::SliderFloat3( "position", _position, -10.0f, 10.0f );
            m_lightSpotPosition = { _position[0], _position[1], _position[2] };

            g_lightSpotDirection = engine::CVec3::normalize( m_lightSpotDirection );
            g_lightSpotPosition = m_lightSpotPosition;

            _lightPtr->direction = g_lightSpotDirection;
            _lightPtr->position = g_lightSpotPosition;

            ImGui::SliderFloat( "znear", &g_znearSpot, 0.1f, 5.0f );
            ImGui::SliderFloat( "zfar", &g_zfarSpot, g_znearSpot, 20.0f );
            ImGui::SliderFloat( "fov", &g_fovSpot, 20.0f, 150.0f );
        }
    }

    engine::CMainRenderer* m_rendererPtr;
    engine::CMeshRenderer* m_meshRendererPtr;

    std::vector< engine::CILight* > m_lights;
    std::vector< std::string > m_lightsNames;
    std::string m_lightSelectedName;
    int m_lightSelectedIndex;

    engine::CVec3 m_lightDirDirection;
    engine::CVec3 m_lightPointDirection;
    engine::CVec3 m_lightSpotDirection;

    engine::CVec3 m_lightPointPosition;
    engine::CVec3 m_lightSpotPosition;
};

void renderScene( engine::CICamera* cameraPtr,
                  engine::CShader* shaderPtr,
                  const std::vector< engine::CIRenderable* >& renderables );

void renderDepthMap( engine::CILight* lightPtr,
                     engine::CVertexArray* quadVAO,
                     engine::CShader* shaderPtr,
                     engine::CShadowMap* shadowMapPtr );

int main()
{
    auto _app = new engine::COpenGLApp();
    _app->init();

    auto _ui = new ApplicationUi( engine::COpenGLApp::GetWindow()->context() );
    _ui->init();

    _app->setUi( std::unique_ptr< ApplicationUi >( _ui ) );
    _ui->setRenderer( _app->renderer() );
    _ui->setMeshRenderer( _app->renderer()->meshRenderer() );

    auto _cameraProjData = engine::CCameraProjData();
    _cameraProjData.projection  = engine::eCameraProjection::PERSPECTIVE;
    _cameraProjData.fov         = 45.0f;
    _cameraProjData.aspect      = engine::COpenGLApp::GetWindow()->aspect();
    _cameraProjData.zNear       = 0.1f;
    _cameraProjData.zFar        = 50.0f;

    auto _camera = new engine::COrbitCamera( "orbit",
                                             { 0.0f, 0.0f, 3.0f },
                                             { 0.0f, 0.0f, 0.0f },
                                             engine::eAxis::Y,
                                             _cameraProjData,
                                             engine::COpenGLApp::GetWindow()->width(),
                                             engine::COpenGLApp::GetWindow()->height() );

    _app->scene()->addCamera( std::unique_ptr< engine::CICamera >( _camera ) );

    auto _plane     = engine::CMeshBuilder::createPlane( 20.0f, 20.0f, engine::eAxis::Y );
    auto _boxy      = engine::CMeshBuilder::createBox( 0.25f, 0.5f, 1.0f );
    auto _sphery    = engine::CMeshBuilder::createSphere( 0.5f );
    auto _ellipsy   = engine::CMeshBuilder::createEllipsoid( 0.2f, 0.4f, 0.6f );
    auto _cylindyX  = engine::CMeshBuilder::createCylinder( 0.25f, 0.5f, engine::eAxis::X );
    auto _cylindyY  = engine::CMeshBuilder::createCylinder( 0.25f, 0.5f, engine::eAxis::Y );
    auto _cylindyZ  = engine::CMeshBuilder::createCylinder( 0.25f, 0.5f, engine::eAxis::Z );
    auto _capsulyX  = engine::CMeshBuilder::createCapsule( 0.25f, 0.5f, engine::eAxis::X );
    auto _capsulyY  = engine::CMeshBuilder::createCapsule( 0.25f, 0.5f, engine::eAxis::Y );
    auto _capsulyZ  = engine::CMeshBuilder::createCapsule( 0.25f, 0.5f, engine::eAxis::Z );
    auto _arrowyX   = engine::CMeshBuilder::createArrow( 0.5f, engine::eAxis::X );
    auto _arrowyY   = engine::CMeshBuilder::createArrow( 0.5f, engine::eAxis::Y );
    auto _arrowyZ   = engine::CMeshBuilder::createArrow( 0.5f, engine::eAxis::Z );
    auto _axy       = engine::CMeshBuilder::createAxes( 0.5f );

    std::string _modelpath;
    _modelpath += ENGINE_RESOURCES_PATH;
    _modelpath += "models/chassis.stl";

    auto _model = engine::CMeshBuilder::createModelFromFile( _modelpath );

    _boxy->position      = { -1.0f, 1.0f, -1.0f };
    _sphery->position    = { -1.0f, 1.0f,  1.0f };
    _ellipsy->position   = {  1.0f, 1.0f,  1.0f };
    _cylindyX->position  = {  1.0f, 1.0f, -1.0f };

    _cylindyY->position  = { -1.0f, 2.0f, -1.0f };
    _cylindyZ->position  = { -1.0f, 2.0f,  1.0f };
    _capsulyX->position  = {  1.0f, 2.0f,  1.0f };
    _capsulyY->position  = {  1.0f, 2.0f, -1.0f };

    _capsulyZ->position  = { -1.0f, 3.0f, -1.0f };
    _arrowyX->position   = { -1.0f, 3.0f,  1.0f };
    _arrowyY->position   = {  1.0f, 3.0f,  1.0f };
    _arrowyZ->position   = {  1.0f, 3.0f, -1.0f };

    _axy->position       = { 0.0f, 1.0f, 0.0f };
    _model->position     = { 0.0f, 2.0f, 0.0f };

    _boxy->scale = { 0.2f, 0.2f, 0.2f };

    std::vector< engine::CIRenderable* > _renderables = { _plane, _boxy, _sphery, _ellipsy, 
                                                          _cylindyX, _cylindyY, _cylindyZ,
                                                          _capsulyX, _capsulyY, _capsulyZ,
                                                          _arrowyX, _arrowyY, _arrowyZ,
                                                          _axy, _model };

    for ( size_t i = 0; i < _renderables.size(); i++ )
        _app->scene()->addRenderable( std::unique_ptr< engine::CIRenderable >( _renderables[i] ) );

    // give the renderables a little rotation and scale
    std::default_random_engine _randomGenerator;
    std::uniform_real_distribution< float > _randomDistribution( 0.5f, 1.0f );
    for ( size_t i = 0; i < _renderables.size(); i++ )
    {
        if ( i == 0 ) // leave plane unchanged
            continue;

        _renderables[i]->rotation = engine::CMat4::fromEuler( { _randomDistribution( _randomGenerator ) * (float) ENGINE_PI,
                                                                _randomDistribution( _randomGenerator ) * (float) ENGINE_PI,
                                                                _randomDistribution( _randomGenerator ) * (float) ENGINE_PI } );
        float _scale = _randomDistribution( _randomGenerator );
        _renderables[i]->scale = { _scale, _scale, _scale };
    }

    auto _shader = engine::CShaderManager::GetCachedShader( "basic3d_no_textures" );
    ENGINE_ASSERT( _shader, "Could not grab the basic3d shader to render the scene :(" );

    /* load the shader in charge of depth-map visualization */
    std::string _baseNameShadowMapViz = std::string( ENGINE_EXAMPLES_PATH ) + "shadows/shaders/shadowmap_visualization";
    auto _shaderShadowMapViz = engine::CShaderManager::CreateShaderFromFiles( "shadowmap_visualization_shader",
                                                                             _baseNameShadowMapViz + "_vs.glsl",
                                                                             _baseNameShadowMapViz + "_fs.glsl" );
    ENGINE_ASSERT( _shaderShadowMapViz, "Couldn't load the visualization shader to check the depth-map T_T" );

    // configure render options
    g_renderOptions.mode = engine::eRenderMode::NORMAL;
    g_renderOptions.useFrustumCulling = true;
    g_renderOptions.cullingGeom = engine::eCullingGeom::BOUNDING_BOX;
    g_renderOptions.useFaceCulling = false;
    g_renderOptions.useShadowMapping = true;
    g_renderOptions.renderGizmos = false;
    g_renderOptions.viewportWidth = engine::COpenGLApp::GetWindow()->width();
    g_renderOptions.viewportHeight = engine::COpenGLApp::GetWindow()->height();
    g_renderOptions.cameraPtr = _camera;
    g_renderOptions.lightPtr = _ui->selectedLight();
    g_renderOptions.shadowMapPtr = nullptr;
    g_renderOptions.renderTargetPtr = nullptr;

    /* vao used for shadow-mapping visualization */
    engine::float32 _quad_buffData[] = {
     /*|  positions |     uvs    |*/
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f
    };

    engine::uint32 _quad_indices[] = {
        0, 1, 2, 
        0, 2, 3
    };

    engine::CVertexBufferLayout _layout = { { "pos", engine::eElementType::Float2, false },
                                            { "uv", engine::eElementType::Float2, false } };

    auto _quad_vbuffer = new engine::CVertexBuffer( _layout,
                                                    engine::eBufferUsage::STATIC,
                                                    sizeof( _quad_buffData ),
                                                    _quad_buffData );;

    auto _quad_ibuffer = new engine::CIndexBuffer( engine::eBufferUsage::STATIC,
                                                   6, _quad_indices );

    auto _quad_varray = new engine::CVertexArray();
    _quad_varray->addVertexBuffer( _quad_vbuffer );
    _quad_varray->setIndexBuffer( _quad_ibuffer );

    while( _app->active() )
    {
        if ( engine::CInputHandler::CheckSingleKeyPress( ENGINE_KEY_ESCAPE ) )
            break;
        else if ( engine::CInputHandler::CheckSingleKeyPress( ENGINE_KEY_SPACE ) )
            _camera->setActiveMode( false );
        else if ( engine::CInputHandler::CheckSingleKeyPress( ENGINE_KEY_ENTER ) )
            _camera->setActiveMode( true );

        if ( _camera->type() == engine::CFpsCamera::GetStaticType() )
        {
            if ( _camera->active() )
                engine::COpenGLApp::GetWindow()->disableCursor();
            else
                engine::COpenGLApp::GetWindow()->enableCursor();
        }

        engine::CDebugDrawer::DrawLine( { 0.0f, 0.0f, 0.0f }, { 5.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } );
        engine::CDebugDrawer::DrawLine( { 0.0f, 0.0f, 0.0f }, { 0.0f, 5.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } );
        engine::CDebugDrawer::DrawLine( { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 1.0f } );

        // use user-selected light
        auto lightPtr = g_renderOptions.lightPtr = _ui->selectedLight();

        // configure shadow-map range
        engine::CShadowMapRangeConfig _config;
        if ( lightPtr->type() == engine::eLightType::DIRECTIONAL )
            _config.dirLightPtr = dynamic_cast< engine::CDirectionalLight* >( lightPtr );
        if ( lightPtr->type() == engine::eLightType::POINT )
            _config.pointLightPtr = dynamic_cast< engine::CPointLight* >( lightPtr );
        if ( lightPtr->type() == engine::eLightType::SPOT )
            _config.spotLightPtr = dynamic_cast< engine::CSpotLight* >( lightPtr );
    
        if ( g_useAutofixToCamera && lightPtr->type() == engine::eLightType::DIRECTIONAL )
        {
            _config.type        = engine::eShadowRangeType::AUTOFIX_CAMERA;
            _config.worldUp     = g_worldUp;
            _config.cameraPtr   = _camera;
            _config.extraWidth  = g_extraWidth;
            _config.extraHeight = g_extraHeight;
            _config.extraDepth  = g_extraDepth;
        }
        else
        {
            _config.type            = engine::eShadowRangeType::FIXED_USER;
            _config.worldUp         = g_worldUp;
            _config.focusPoint      = g_focusPoint;
            if ( lightPtr->type() == engine::eLightType::DIRECTIONAL )
            {
                _config.clipSpaceWidth  = g_widthDir;
                _config.clipSpaceHeight = g_heightDir;
                _config.clipSpaceDepth  = g_depthDir;
            }
            else if ( lightPtr->type() == engine::eLightType::POINT )
            {
                _config.clipSpaceZNear  = g_znearPoint;
                _config.clipSpaceZFar   = g_zfarPoint;
                _config.clipSpaceFov    = g_fovPoint;
            }
            else if ( lightPtr->type() == engine::eLightType::SPOT )
            {
                _config.clipSpaceZNear  = g_znearSpot;
                _config.clipSpaceZFar   = g_zfarSpot;
                _config.clipSpaceFov    = g_fovSpot;
            }
        }
        g_renderOptions.shadowMapRangeConfig = _config;

        _app->update();
        _app->beginRendering();

        /****************************************************/
        // // render the objects with plain colors (just to check)
        // renderScene( _camera, _shader, _renderables );

        // render our scene
        _app->renderer()->render( _app->scene(), g_renderOptions );

        // visualize the shadow-map
        renderDepthMap( lightPtr, _quad_varray, _shaderShadowMapViz, _app->renderer()->shadowMap() );

        /****************************************************/

        _app->renderScene();
        _app->renderDebug();

        if ( !_camera->active() )
            _app->renderUi();

        _app->endRendering();
    }

    return 0;
}

void renderScene( engine::CICamera* cameraPtr,
                  engine::CShader* shaderPtr,
                  const std::vector< engine::CIRenderable* >& renderables )
{
    shaderPtr->bind();
    shaderPtr->setMat4( "u_tView", cameraPtr->matView() );
    shaderPtr->setMat4( "u_tProj", cameraPtr->matProj() );

    for ( auto renderablePtr : renderables )
    {
        shaderPtr->setVec3( "u_color", renderablePtr->material()->ambient );
        shaderPtr->setMat4( "u_tModel", renderablePtr->matModel() );
        renderablePtr->render();

        auto _bbox = renderablePtr->bbox();
        auto _bsphere = renderablePtr->bsphere();

        engine::CDebugDrawer::DrawBox( _bbox.size, _bbox.worldTransform, { 0.2f, 0.2f, 0.8f } );
        engine::CDebugDrawer::DrawSphere( _bsphere.radius, engine::CMat4::translation( _bsphere.worldPosition ), { 0.2f, 0.8f, 0.2f } );
    }

    shaderPtr->unbind();
}

void renderDepthMap( engine::CILight* lightPtr,
                     engine::CVertexArray* quadVAO,
                     engine::CShader* shaderPtr,
                     engine::CShadowMap* shadowMapPtr )
{
    glDisable( GL_DEPTH_TEST );
    glViewport( 0, 0, 256, 256 );
    shaderPtr->bind();
    shadowMapPtr->frameBuffer()->getTextureAttachment( "shadow_depth_attachment" )->bind();
    quadVAO->bind();

    if ( lightPtr->type() == engine::eLightType::POINT || lightPtr->type() == engine::eLightType::SPOT )
    {
        shaderPtr->setInt( "u_linearizeDepth", 1 );
        shaderPtr->setFloat( "u_znear", g_znearPoint );
        shaderPtr->setFloat( "u_zfar", g_zfarPoint );
    }
    else
    {
        shaderPtr->setInt( "u_linearizeDepth", 0 );
    }

    glDrawElements( GL_TRIANGLES, quadVAO->indexBuffer()->count(), GL_UNSIGNED_INT, 0 );

    quadVAO->unbind();
    shadowMapPtr->frameBuffer()->getTextureAttachment( "shadow_depth_attachment" )->unbind();
    shaderPtr->unbind();
    glEnable( GL_DEPTH_TEST );
    glViewport( 0, 0, engine::COpenGLApp::GetWindow()->width(), engine::COpenGLApp::GetWindow()->height() );
}
