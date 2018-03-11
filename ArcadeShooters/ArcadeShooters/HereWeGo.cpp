#include <iostream>
using namespace std;
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
//enum characters { PLAYER1, PLAYER2 };
//enum difficulty{EASY, NORMAL, HARD, INSANE};
enum directions{UP, DOWN, LEFT, RIGHT};

//enum stages{EXTRA, STAGE1, STAGE2, STAGE3, STAGE4, STAGE5, STAGE6};
//void roll(int x, int y, int dir, int time, bool collision);
//class players {
//public:
//	void initpc(int character, int x, int y);
//	void drawpc(ALLEGRO_BITMAP);
//private:
//	int xpos;
//	int ypos;
//
//};

int main() {
	bool pause = false;
	bool redraw = false;
	int screenwidth = 1200;
	int screenheight = 800;
	int player_x = screenwidth / 2;
	int player_y = (screenheight * 3) / 4;
	int movespeed = 8;
	int playersize = 40;
	int hitboxsize = 2;
	//int itemsize = 10;
	//int largeitemsize = 20;
//	int stage = 1;
	bool keys[8]{ false, false, false, false, false, false, false, false};
	
	al_init();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	ALLEGRO_DISPLAY* display = al_create_display(screenwidth, screenheight);
	ALLEGRO_BITMAP* pc1 = al_create_bitmap(playersize, playersize);
//	ALLEGRO_BITMAP* pc2 = al_create_bitmap(playersize + 20, playersize + 20);
	ALLEGRO_BITMAP* pc1_hitbox = al_create_bitmap(hitboxsize, hitboxsize);
//	ALLEGRO_BITMAP* pc2_hitbox = al_create_bitmap(hitboxsize, hitboxsize);
	ALLEGRO_TIMER* timer = al_create_timer(0.02);
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_EVENT_QUEUE*event_queue = al_create_event_queue();
	al_install_keyboard();
	al_set_target_bitmap(pc1);
	al_clear_to_color(al_map_rgb(255, 200, 200));
	al_set_target_bitmap(pc1_hitbox);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_flip_display();
	al_start_timer(timer);
	while (!pause) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (keys[UP]&&player_y > 0) {
				player_y -= movespeed;
			}
			if (keys[DOWN]&& player_y < screenheight-playersize) {
				player_y += movespeed;
			}
			if (keys[LEFT]&& player_x > 0) {
				player_x -= movespeed;
			}
			if (keys[RIGHT]&& player_x < screenwidth-playersize) {
				player_x += movespeed;
			}
			if (keys[4]) {
				movespeed/4;
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[4] = true;
				break;
				
			case ALLEGRO_KEY_ESCAPE:
				pause = true;
				return 0;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[4] = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(pc1, player_x, player_y, 0);
			al_draw_bitmap(pc1_hitbox, player_x + (playersize / 2), player_y + (playersize / 2), 0);

			al_flip_display();

		}
		
	}
	al_destroy_bitmap(pc1);
	al_destroy_bitmap(pc1_hitbox);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	return 0;
}