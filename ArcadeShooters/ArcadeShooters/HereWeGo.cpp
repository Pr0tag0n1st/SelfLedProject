#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

enum difficulty{EASY, NORMAL, HARD, INSANE};
enum directions{UP, DOWN, LEFT, RIGHT};
void roll(int x, int y, int dir, int time, bool collision);

int main() {
	int screenwidth = 1200;
	int screenheight = 800;
	int playersize = 40;
	int hitboxsize = 4;
	int itemsize = 10;
	int largeitemsize = 20;
	int stage = 1;
	bool keys[5]{ false, false, false, false, false };
	bool focus = false;
	
	al_init();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(screenwidth, screenheight);
	ALLEGRO_BITMAP* pc1 = al_create_bitmap(playersize, playersize);
	ALLEGRO_BITMAP* pc2 = al_create_bitmap(playersize + 20, playersize + 20);
	ALLEGRO_BITMAP* pc3 = al_create_bitmap(playersize - 20, playersize - 20);
	ALLEGRO_BITMAP* pc1_hitbox = al_create_bitmap(hitboxsize, hitboxsize);
	ALLEGRO_BITMAP* pc2_hitbox = al_create_bitmap(hitboxsize, hitboxsize);
	ALLEGRO_BITMAP* pc3_hitbox = al_create_bitmap(hitboxsize - 2, hitboxsize - 2);
	ALLEGRO_TIMER* timer = al_create_timer(0.2);
	ALLEGRO_FONT* font = NULL;
	
}