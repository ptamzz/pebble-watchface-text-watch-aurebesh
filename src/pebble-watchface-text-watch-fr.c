#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "time_calculation.h"

#define MY_UUID { 0xD3, 0x53, 0x12, 0x05, 0x0F, 0x86, 0x4C, 0x83, 0xB2, 0x34, 0xA7, 0x73, 0x4E, 0x78, 0xB9, 0x70 }
PBL_APP_INFO(MY_UUID,
             "Aurebesh Text Watch", "chadrien",
             1, 4, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
TextLayer hours;
TextLayer minutes_layer;
GFont hours_layer_font;
GFont minutes_layer_font;
GRect hours_end_position;
GRect minutes_layer_end_position;
PropertyAnimation hours_animation;
PropertyAnimation minutes_layer_animation;
bool initialized;

static const char* const SPECIAL_TEN_ONE = "et un";

void update_hours(PblTm* time)
{
  const char* hours_string = get_hours_string(time->tm_hour);

  if (text_layer_get_text(&hours) != hours_string) {
    text_layer_set_text(&hours, hours_string);

    if (initialized) {
      layer_set_frame(&hours.layer, GRect(144, 20, 144, 42));
      property_animation_init_layer_frame(&hours_animation, &hours.layer, NULL, &hours_end_position);
      animation_schedule(&hours_animation.animation);
    }
  }
}

void update_minutes(PblTm* time)
{
  const char* minutes_string = get_minutes_string(time->tm_min);

  if (text_layer_get_text(&minutes_layer) != minutes_string) {
    text_layer_set_text(&minutes_layer, minutes_string);

    if (initialized) {
      layer_set_frame(&minutes_layer.layer, GRect(144, 20 + 42 - 5, 144, 29 * 2));
      property_animation_init_layer_frame(&minutes_layer_animation, &minutes_layer.layer, NULL, &minutes_layer_end_position);
      animation_schedule(&minutes_layer_animation.animation);
    }
  }
}

void update_time(PblTm* time)
{
  update_hours(time);
  update_minutes(time);
}

void handle_tick(AppContextRef app_ctx, PebbleTickEvent *event)
{
  (void)app_ctx;

  PblTm* time = event->tick_time;

  update_time(time);

  if (initialized == false) {
    initialized = true;
  }
}

void init_text_layer(TextLayer* text_layer, GRect position, GFont font)
{
  text_layer_init(text_layer, position);
  text_layer_set_text_color(text_layer, GColorWhite);
  text_layer_set_background_color(text_layer, GColorClear);
  layer_set_clips((Layer *) text_layer, false);
  text_layer_set_font(text_layer, font);

  layer_add_child(&window.layer, &text_layer->layer);
}

void handle_init(AppContextRef ctx)
{
  (void)ctx;

  PblTm time;

  resource_init_current_app(&RESOURCES_AUREBESH_TEXT_WATCH);

  hours_end_position = GRect(0, 35, 144, 28);
  minutes_layer_end_position = GRect(0, 40 + 28 - 5, 144, 28 * 2);

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  hours_layer_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_AUREBESH_BOLD_27));
  minutes_layer_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_AUREBESH_27));

  init_text_layer(&hours, hours_end_position, hours_layer_font);
  init_text_layer(&minutes_layer, minutes_layer_end_position, minutes_layer_font);

  get_time(&time);
  update_time(&time);
}

void pbl_main(void *params)
{
  initialized = false;

  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = MINUTE_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
