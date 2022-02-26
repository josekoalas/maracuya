//project verse, 2017-2022
//by jose pazos perez

#pragma once

#include "scene.h"

#include "log.h"
#include "input.h"
#include "r_graphics.h"
#include "f_time.h"

namespace Fresa::System
{
    //: Example of a hardcoded render system
    //: This is very basic and not elegant, it will be reworked in the future

    inline Graphics::DrawID draw_id_cube;
    
    inline Clock::time_point start_time = time();
    
    inline const std::vector<Graphics::Projection> projections = {
        Graphics::PROJECTION_ORTHOGRAPHIC,
        Graphics::Projection(Graphics::PROJECTION_ORTHOGRAPHIC | Graphics::PROJECTION_SCALED),
        Graphics::PROJECTION_PERSPECTIVE,
        Graphics::Projection(Graphics::PROJECTION_PERSPECTIVE | Graphics::PROJECTION_SCALED),
    };
    inline int proj_i = 0;
    
    struct SomeSystem : PhysicsUpdate<SomeSystem, PRIORITY_MOVEMENT>, RenderUpdate<SomeSystem> {
        inline static void update() {
            //: Sample camera update
            if (Input::key_down(SDLK_d))
                Graphics::camera.pos.x += 300.0f * Time::physics_delta;
            if (Input::key_down(SDLK_a))
                Graphics::camera.pos.x -= 300.0f * Time::physics_delta;
            
            if (Graphics::camera.proj_type & Graphics::PROJECTION_PERSPECTIVE) {
                if (Input::key_down(SDLK_q))
                    Graphics::camera.pos.y += 300.0f * Time::physics_delta;
                if (Input::key_down(SDLK_e))
                    Graphics::camera.pos.y -= 300.0f * Time::physics_delta;
                if (Input::key_down(SDLK_w))
                    Graphics::camera.pos.z -= 300.0f * Time::physics_delta;
                if (Input::key_down(SDLK_s))
                    Graphics::camera.pos.z += 300.0f * Time::physics_delta;
            } else {
                if (Input::key_down(SDLK_w))
                    Graphics::camera.pos.y -= 300.0f * Time::physics_delta;
                if (Input::key_down(SDLK_s))
                    Graphics::camera.pos.y += 300.0f * Time::physics_delta;
            }
            
            if (Input::key_pressed(SDLK_TAB)) {
                proj_i = (proj_i + 1) % projections.size();
                Graphics::camera.proj_type = projections.at(proj_i);
                Graphics::updateCameraProjection(Graphics::camera);
                Graphics::win.scaled_ubo = (Graphics::camera.proj_type & Graphics::PROJECTION_SCALED) ?
                                            Graphics::API::getScaledWindowUBO(Graphics::win) :
                                            Graphics::UniformBufferObject{glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f)};
            }
        }
        
        inline static void render() {
            static bool init = false;
            if (not init) {
                draw_id_cube = Graphics::getDrawID_Cube(Graphics::SHADER_DRAW_COLOR);
                Graphics::camera.pos = glm::vec3(-0.5f*Config::resolution.x, -0.5f*Config::resolution.y, 500.0f);
                init = true;
            }
            
            float t = sec(time() - start_time);
            
            //: Cubes
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f) * 50.0f);
            model = glm::rotate(model, t * 1.570796f, glm::vec3(0.0f, 1.0f, 0.0f));
            Graphics::draw(draw_id_cube, model);
        }
    };
}
