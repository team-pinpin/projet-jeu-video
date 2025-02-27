#pragma once

#include <raylib.h>

#include "base/components/Position.h"
#include "core/Probe.h"
#include "core/Time.h"
#include "core/World.h"
#include "core/glue/Glue.h"
#include "core/glue/ImGuiExtension.h"

#include "editor/FPSCounter.h"
#include "editor/Panel.h"
#include "editor/model/Model.h"

namespace editor
{
    class Editor
    {
    private:
        Model _model;
        utils::Vector<utils::OwnPtr<Panel>> _panels{};

    public:
        Editor(utils::RefPtr<core::World> world) :
            _model{world}
        {
        }

        template <typename TPanel, typename... TArgs>
        TPanel &open(TArgs &&... args)
        {
            auto ptr = utils::own<TPanel>(std::forward<TArgs>(args)...);
            auto &ref = *ptr;
            _panels.push_back(ptr);
            return ref;
        }

        void update(core::Time &time)
        {
            _model.fps.mesure();

            _model.update_time.mesure([&]() {
                _model.world->update(time);

                _panels.foreach ([&](auto &panel) {
                    panel->update(_model, time);
                    return utils::Iteration::CONTINUE;
                });
            });
        }

        void render()
        {
            _model.render_time.mesure([&]() {
                _panels.foreach ([this](auto &panel) {
                    panel->render(_model);

                    return utils::Iteration::CONTINUE;
                });
            });
        }

        void display()
        {
            _model.display_time.mesure([&]() {
                ImGui::DockSpaceOverViewport();

                _panels.foreach ([this](auto &panel) {
                    panel->do_display(_model);

                    return utils::Iteration::CONTINUE;
                });
            });
        }
    };
} // namespace editor
