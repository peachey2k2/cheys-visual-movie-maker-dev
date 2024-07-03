#include "editor/timeline/ruler.h"

#include "editor/tab.h"
#include "editor/timeline/timeline.h"

using namespace godot;

VMTTimeline *timeline;

void VMTTimelineRuler::_bind_methods() {
}

VMTTimelineRuler::VMTTimelineRuler() {
    timeline = VisualMovieTab::get_singleton()->get_timeline();
    def_font = ThemeDB::get_singleton()->get_fallback_font();
    set_clip_contents(true);
    set_custom_minimum_size(Size2(0, 20));
    add_theme_stylebox_override("panel", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("panel", "Tree"));
}

VMTTimelineRuler::~VMTTimelineRuler() {
}

void VMTTimelineRuler::_draw() {
    float scale = timeline->get_zoom_factor();
    Rect2 rect = timeline->get_timeline_visible_rect();
    float start = rect.position.x - fmod(rect.position.x, 200);
    float end = rect.position.x + rect.size.x;

    for (float i = start - rect.position.x; i < end - rect.position.x; i += 200) {
        draw_line(Vector2(i, 0), Vector2(i, 20), Color(0.5, 0.5, 0.5, 1));
        auto time = VisualMovieTab::get_singleton()->to_time_seperated((i + rect.position.x) / scale);
        String str = String::num(time.hours) + ":" + String::num(time.minutes) + ":" + String::num(time.seconds) + "." + String::num(time.milliseconds);
        draw_string(def_font, Vector2(i + 5, 12), str, HORIZONTAL_ALIGNMENT_LEFT, -1, 12, Color(0.5, 0.5, 0.5, 1));
    }
}