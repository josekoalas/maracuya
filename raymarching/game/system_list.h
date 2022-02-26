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

    inline Graphics::DrawID draw_id;
    
    struct SomeSystem : PhysicsUpdate<SomeSystem, PRIORITY_MOVEMENT>, RenderUpdate<SomeSystem> {
        inline static void update() {
            
        }
        
        inline static void render() {
            static bool init = false;
            if (not init) {
                draw_id = Graphics::getDrawID(Graphics::Vertices::rect_vertices_color, Graphics::Vertices::rect_indices, "draw_test");
                Graphics::camera.proj_type = Graphics::PROJECTION_NONE;
                Graphics::updateCameraProjection(Graphics::camera);
                Graphics::camera.pos = glm::vec3(0.0f);
                init = true;
            }
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(2.0f));
            Graphics::draw(draw_id, model);
        }
    };
}
