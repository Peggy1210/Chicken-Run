#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define MAX 100000
// ALLEGRO Variables
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *background0 = NULL; ALLEGRO_BITMAP *background1 = NULL; ALLEGRO_BITMAP *background1_1 = NULL; ALLEGRO_BITMAP *background1_2 = NULL; ALLEGRO_BITMAP *background1_3 = NULL; ALLEGRO_BITMAP *background1_4 = NULL; ALLEGRO_BITMAP *background2 = NULL; ALLEGRO_BITMAP *background2_1 = NULL; ALLEGRO_BITMAP *background2_2 = NULL; ALLEGRO_BITMAP *background2_3 = NULL; ALLEGRO_BITMAP *background3 = NULL; ALLEGRO_BITMAP *background4 = NULL; ALLEGRO_BITMAP *background5 = NULL;
ALLEGRO_BITMAP *manga1 = NULL; ALLEGRO_BITMAP *manga2 = NULL; ALLEGRO_BITMAP *manga3 = NULL; ALLEGRO_BITMAP *manga4 = NULL; ALLEGRO_BITMAP *manga5 = NULL; ALLEGRO_BITMAP *manga6 = NULL; ALLEGRO_BITMAP *manga7 = NULL; ALLEGRO_BITMAP *manga8 = NULL; ALLEGRO_BITMAP *manga9 = NULL; ALLEGRO_BITMAP *manga10 = NULL; ALLEGRO_BITMAP *manga11 = NULL; ALLEGRO_BITMAP *manga12 = NULL;
ALLEGRO_BITMAP *settings0 = NULL; ALLEGRO_BITMAP *settings1 = NULL; ALLEGRO_BITMAP *settings2 = NULL; ALLEGRO_BITMAP *settings3 = NULL; ALLEGRO_BITMAP *settings4 = NULL; ALLEGRO_BITMAP *settings5 = NULL; ALLEGRO_BITMAP *settings6 = NULL; ALLEGRO_BITMAP *settings7 = NULL;
ALLEGRO_BITMAP *character_menu1 = NULL; ALLEGRO_BITMAP *character_menu2 = NULL; ALLEGRO_BITMAP *character_menu3 = NULL; ALLEGRO_BITMAP *character_menu4 = NULL;
ALLEGRO_BITMAP *character_menu5 = NULL; ALLEGRO_BITMAP *character_menu6 = NULL; ALLEGRO_BITMAP *character_menu7 = NULL; ALLEGRO_BITMAP *character_menu8 = NULL; ALLEGRO_BITMAP *character_menu9 = NULL;
ALLEGRO_BITMAP *loading1 = NULL; ALLEGRO_BITMAP *loading2 = NULL; ALLEGRO_BITMAP *loading3 = NULL;
ALLEGRO_BITMAP *win = NULL; ALLEGRO_BITMAP *lose = NULL;
ALLEGRO_BITMAP *gift0 = NULL;
ALLEGRO_BITMAP *friend1 = NULL; ALLEGRO_BITMAP *friend2 = NULL;
ALLEGRO_BITMAP *life0 = NULL; ALLEGRO_BITMAP *life1 = NULL; ALLEGRO_BITMAP *life2 = NULL; ALLEGRO_BITMAP *life3 = NULL; ALLEGRO_BITMAP *life4 = NULL; ALLEGRO_BITMAP *life5 = NULL;
ALLEGRO_TIMER *update_timer = NULL;
ALLEGRO_SAMPLE *song1 = NULL;
ALLEGRO_FONT *font = NULL;

const char *title = "Final Project Team 030";
const float FPS = 60;
const int WIDTH = 400, HEIGHT = 600;
typedef struct{
    int x;
    int y;
    ALLEGRO_BITMAP *image_path1;
    ALLEGRO_BITMAP *image_path2;
    int life;
}Character;

typedef struct{
    int x;
    int y;
    int life;
}Weapon;

Character chick;
Character rabbit;
Character bee, queen, spider, bat, ghost;
Character Chick1, Chick2, Chick3, Chick4;
Character Rabbit1, Rabbit2, Rabbit3, Rabbit4;
Weapon gift[MAX];
Weapon corn[MAX];
Weapon bullet[MAX];

//system control
bool key_state[ALLEGRO_KEY_MAX];
bool done = false;
bool pause = false;
int window = 0;
//score control
int ranking = 1;
//settings
int sound = 0;  // sound total control
int settings_menu = 0;
int settings_menu_done = 0;
// mangapage
int mangapage = 0;
//character menu
int chick_menu = 2;
int rabbit_menu = 1;
int character_menu_done = 0;
//main menu
int main_menu_done = 0;
int main_menu = 0;
//map menu
int map_menu_done = 0;
int map_menu = 1;
int mapunlock = 0;
//game control
const int WIN = 5;
const int LOSE = 6;
int stage1 = 0;
int stage2 = 0;
bool dirx = true;
bool diry = false;
int count_corn = 0;
int count_bullet = 0;
int count_gift = 0;
int bullet_ctrl = 0;
int gift_state = 0;
int gift_timer = 0;

void show_err_msg();
void game_init();
void game_begin();
void event_loop();
void game_destroy();

void change_window();
void game_update();
void window0_update();
void window0_draw();
void window1_update();
void window1_draw();
void window2_update();
void window2_draw();
void window3_update();
void window3_draw();
void window4_update();
void window4_draw();
void window5_update();
void window5_draw();
void settings_update();
void settings_draw();
void character_menu_update();
void character_menu_draw();
void loading();
void change_window();

int main(){

    game_init();
    game_begin();
    //loading();
    event_loop();
    game_destroy();

    return 0;
}

void show_err_msg(int msg){
    fprintf(stderr, "unexpected msg: %d\n", msg);
    game_destroy();
    exit(9);
}

void game_init(){
    if(!al_init()){
        show_err_msg(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        show_err_msg(-2);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        show_err_msg(-3);
    }
    if(!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        show_err_msg(-4);
    }

    //Create display
    display = al_create_display(WIDTH, HEIGHT);
    event_queue = al_create_event_queue();
    update_timer = al_create_timer(1.0f/FPS);
    if(display==NULL || event_queue==NULL || update_timer==NULL){
        show_err_msg(-5);
    }

    // Initialize Allegro settings
    al_set_window_position(display, 100, 100);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    //Register Event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(update_timer));

    //start timer
    al_start_timer(update_timer);
}

void game_begin(){
    //Load Sound
    song1 = al_load_sample("media.io_song.wav");
    if(song1==NULL){
        printf("Audio clip sample not loaded\n");
        show_err_msg(-6);
    }
    //start background music
    al_play_sample(song1, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //Load text
    font = al_load_ttf_font("pirulen.ttf", 12, 0);
    if(font==NULL){
        printf("Font not loaded");
        show_err_msg(-7);
    }

    // Load manga
    manga1 = al_load_bitmap("manga1.jpg");
    manga2 = al_load_bitmap("manga2.jpg");
    manga3 = al_load_bitmap("manga3.jpg");
    manga4 = al_load_bitmap("manga4.jpg");
    manga5 = al_load_bitmap("manga5.jpg");
    manga6 = al_load_bitmap("manga6.jpg");
    manga7 = al_load_bitmap("manga7.jpg");
    manga8 = al_load_bitmap("manga8.jpg");
    manga9 = al_load_bitmap("manga9.jpg");
    manga10 = al_load_bitmap("manga10.jpg");
    manga11 = al_load_bitmap("manga11.jpg");
    manga12 = al_load_bitmap("manga12.jpg");
    if(manga1 == NULL || manga2 == NULL || manga3 == NULL || manga4 == NULL || manga5 == NULL || manga6 == NULL || manga7 == NULL || manga8 == NULL || manga9 == NULL || manga10 == NULL || manga11 == NULL || manga12 == NULL){
        printf("manga not loaded\n");
        show_err_msg(-7);
    }

    //Load background
    background0 = al_load_bitmap("background0.jpg");
    background1 = al_load_bitmap("background1.jpg");
    background1_1 = al_load_bitmap("background1_1.jpg");
    background1_2 = al_load_bitmap("background1_2.jpg");
    background1_3 = al_load_bitmap("background1_3.jpg");
    background1_4 = al_load_bitmap("background1_4.jpg");
    background2 = al_load_bitmap("background2.jpg");
    background2_1 = al_load_bitmap("background2_1.jpg");
    background2_2 = al_load_bitmap("background2_2.jpg");
    background2_3 = al_load_bitmap("background2_3.jpg");
    background3 = al_load_bitmap("background3.jpg");
    background4 = al_load_bitmap("background4.jpg");
    background5 = al_load_bitmap("background5.jpg");
    if(background0==NULL || background1==NULL || background1_1==NULL || background1_2==NULL || background1_3==NULL || background1_4==NULL || background2==NULL || background2_1==NULL || background2_2==NULL || background2_3==NULL || background3==NULL || background4==NULL || background5==NULL){
        printf("background not loaded\n");
        show_err_msg(-7);
    }

    //Load settings
    settings0 = al_load_bitmap("settings0.jpg");
    settings1 = al_load_bitmap("settings1.jpg");
    settings2 = al_load_bitmap("settings2.jpg");
    settings3 = al_load_bitmap("settings3.jpg");
    settings4 = al_load_bitmap("settings4.jpg");
    settings5 = al_load_bitmap("settings5.jpg");
    settings6 = al_load_bitmap("settings6.jpg");
    settings7 = al_load_bitmap("settings7.jpg");
    if(settings1 == NULL || settings2 == NULL || settings3 == NULL || settings4 == NULL || settings5 == NULL || settings6 == NULL || settings7 == NULL){
        printf("settings not loaded\n");
        show_err_msg(-7);
    }

    //Load character menu
    character_menu1 = al_load_bitmap("character_menu1.jpg");
    character_menu2 = al_load_bitmap("character_menu2.jpg");
    character_menu3 = al_load_bitmap("character_menu3.jpg");
    character_menu4 = al_load_bitmap("character_menu4.jpg");
    character_menu5 = al_load_bitmap("character_menu5.jpg");
    character_menu6 = al_load_bitmap("character_menu6.jpg");
    character_menu7 = al_load_bitmap("character_menu7.jpg");
    character_menu8 = al_load_bitmap("character_menu8.jpg");
    character_menu9 = al_load_bitmap("character_menu9.jpg");
    if(character_menu1==NULL || character_menu2==NULL || character_menu3==NULL || character_menu4==NULL || character_menu5==NULL || character_menu6==NULL || character_menu7==NULL || character_menu8==NULL || character_menu9==NULL){
        printf("character menu not loaded\n");
        show_err_msg(-7);
    }

    //Load Loading
    loading1 = al_load_bitmap("loading1.jpg");
    loading2 = al_load_bitmap("loading2.jpg");
    loading3 = al_load_bitmap("loading3.jpg");
    if(loading1==NULL || loading2==NULL || loading3==NULL){
        printf("loading image not loaded\n");
        show_err_msg(-7);
    }

    //Load win lose scene
    win = al_load_bitmap("win.png");
    lose = al_load_bitmap("lose.png");
    if(win==NULL || lose==NULL){
        printf("win or lose scene not loaded\n");
        show_err_msg(-7);
    }

    //Load life image
    life0 = al_load_bitmap("life0.png"); life1 = al_load_bitmap("life1.png"); life2 = al_load_bitmap("life2.png"); life3 = al_load_bitmap("life3.png"); life4 = al_load_bitmap("life4.png"); life5 = al_load_bitmap("life5.png");
    if(life0==NULL || life1==NULL || life2==NULL || life3==NULL || life4==NULL || life5==NULL){
        printf("life image not loaded\n");
        show_err_msg(-7);
    }

    //Load enemy image
    bee.image_path1 = al_load_bitmap("bee1.png"); bee.image_path2 = al_load_bitmap("bee2.png");
    queen.image_path1 = al_load_bitmap("queen1.png"); queen.image_path2 = al_load_bitmap("queen2.png");
    spider.image_path1 = al_load_bitmap("spider1.png"); spider.image_path2 = al_load_bitmap("spider2.png");
    bat.image_path1 = al_load_bitmap("bat1.png"); bat.image_path2 = al_load_bitmap("bat2.png");
    ghost.image_path1 = al_load_bitmap("ghost1.png");
    if(bee.image_path1==NULL || bee.image_path2==NULL || queen.image_path1==NULL || queen.image_path2==NULL || spider.image_path1==NULL || spider.image_path2==NULL || bat.image_path1==NULL || bat.image_path2==NULL || ghost.image_path1==NULL){
        printf("enemy image not loaded\n");
        show_err_msg(-7);
    }

    //load gift image
    gift0 = al_load_bitmap("gift.png");
    friend1 = al_load_bitmap("friend1.png"); friend2 = al_load_bitmap("friend2.png");
    if(gift0==NULL || friend1==NULL || friend2==NULL){
        printf("gift image not loaded\n");
        show_err_msg(-7);
    }

/*
    chick.image_path1 = al_load_bitmap("run1_left.png");
    chick.image_path2 = al_load_bitmap("run1_left1.png");
    chick.life = 200;
    chick.x = WIDTH/2;             ////////////////////////////////////
    chick.y = 400;                 ////////////////////////////////////
    bee.life = 100;
    queen.life = 200;
    spider.life = 150;
    bat.life = 250;
    ghost.life = 350;
    bullet_ctrl=0;
    count_bullet=0;
    count_corn=0;
    count_gift=0;
*/
}

//gaming process event
void event_loop(){
    //request the event
    ALLEGRO_EVENT event;
    while(!done){
        al_wait_for_event(event_queue, &event);
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;
        else if(event.type==ALLEGRO_EVENT_KEY_DOWN){
            key_state[event.keyboard.keycode] = true;
            pause = true;
        }
        else if(event.type==ALLEGRO_EVENT_KEY_UP)
            key_state[event.keyboard.keycode] = false;
        else if(event.type==ALLEGRO_EVENT_TIMER){
            if(event.timer.source==update_timer){
                //printf("%d ", window);
                //begin
                if(window==0){
                    window0_update();
                    window0_draw();
                }
                //main menu
                else if(window==1){
                    window1_update();
                    window1_draw();
                }
                //map menu
                else if(window==2){
                    window2_update();
                    window2_draw();
                }
                //map1
                else if(window==3){

                    window3_update();
                    window3_draw();
                }
                //map2
                else if(window==4){
                    window4_update();
                    window4_draw();
                }
                //ending
                else if(window==5){
                    window5_update();
                    window5_draw();
                }
                //character_menu
                else if(window==10){
                    character_menu_update();
                    character_menu_draw();
                }
                //setting
                else if(window==11){
                    settings_update();
                    settings_draw();
                }
            }
        }
    }
}

void window0_update(){
    if(key_state[ALLEGRO_KEY_DOWN] && pause && mangapage<=8){
            mangapage++;
            pause = false;
    }
    else if(key_state[ALLEGRO_KEY_UP] && pause && mangapage>0){
            mangapage--;
            pause = false;
    }
    if(mangapage==9) {
        window = 1;
    }
}
void window0_draw(){
    if(mangapage==0){
        al_draw_bitmap(background0, 0, 0, 0);
        al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255,255,255), 0);
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220, ALLEGRO_ALIGN_CENTRE, "Press \"down\" to start story");
        al_flip_display();
    }
    else if(mangapage==1) al_draw_bitmap(manga1, 0, 0, 0);
    else if(mangapage==2) al_draw_bitmap(manga2, 0, 0, 0);
    else if(mangapage==3) al_draw_bitmap(manga3, 0, 0, 0);
    else if(mangapage==4) al_draw_bitmap(manga4, 0, 0, 0);
    else if(mangapage==5) al_draw_bitmap(manga5, 0, 0, 0);
    else if(mangapage==6) al_draw_bitmap(manga6, 0, 0, 0);
    else if(mangapage==7) al_draw_bitmap(manga7, 0, 0, 0);
    else if(mangapage==8){
        if(mapunlock==2) window5_draw();
        al_draw_bitmap(manga8, 0, 0, 0);
        al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255,255,255), 0);
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220, ALLEGRO_ALIGN_CENTRE, "Press \"down\" to start game");
    }
    al_flip_display();
}

void window1_update(){
    if(main_menu_done==0){
        if(key_state[ALLEGRO_KEY_DOWN] && pause){
            main_menu++;
            pause = false;
        }else if(key_state[ALLEGRO_KEY_UP] && pause && main_menu>0){
            main_menu--;
            pause = false;
        }else if(key_state[ALLEGRO_KEY_ENTER] && pause){
            main_menu_done = 1;
            pause = false;
        }
    }
}
void window1_draw(){
    /*main menu*/
    /*choose character*/
    if(main_menu_done==0){
        if(main_menu%5==0) al_draw_bitmap(background1, 0, 0, 0);
        else if(main_menu%5==1) al_draw_bitmap(background1_1, 0, 0, 0);
        else if(main_menu%5==2) al_draw_bitmap(background1_2, 0, 0, 0);
        else if(main_menu%5==3) al_draw_bitmap(background1_3, 0, 0, 0);
        else if(main_menu%5==4) al_draw_bitmap(background1_4, 0, 0, 0);
        al_flip_display();
    }else if(main_menu_done==1){
        if(main_menu%5==1) {
            window = 10;
            main_menu = 0;
            main_menu_done = 0;
            loading();
        }else if(main_menu%5==2){
            window = 11;
            main_menu = 0;
            main_menu_done = 0;
        }else if(main_menu%5==3){
            window = 0;
            main_menu = 0;
            main_menu_done = 0;
            mangapage = 0;
            loading();
        }else if(main_menu%5==4) done = true;
    }
}

void window2_update(){
    if(map_menu_done==0){
        if(key_state[ALLEGRO_KEY_LEFT] && mapunlock && pause) {
            map_menu = 1;
            pause = false;
        }
        if(key_state[ALLEGRO_KEY_RIGHT] && mapunlock && pause) {
            map_menu = 2;
            pause = false;
        }
        if(key_state[ALLEGRO_KEY_ENTER] && pause){
            map_menu_done = 1;
            pause = false;
        }
    }
}
void window2_draw(){
    /*map*/
    if(map_menu_done==0){
        if(map_menu==1 && !mapunlock) al_draw_bitmap(background2_1, 0, 0, 0);
        if(map_menu==1 && mapunlock) al_draw_bitmap(background2_2, 0, 0, 0);
        if(map_menu==2 && mapunlock) al_draw_bitmap(background2_3, 0, 0, 0);
        al_flip_display();
    }else if(map_menu_done==1){
        if(map_menu==1){
            stage1 = 0;
            dirx = true;
            diry = false;
            chick.life = 100;
            chick.x = WIDTH/2;
            chick.y = 400;
            bee.life = 100;
            queen.life = 200;
            bullet_ctrl = 0;
            count_bullet = 0;
            count_corn = 0;
            count_gift = 0;
            gift_state = 0;
            gift_timer = 0;
            loading();
            window = 3;
            map_menu_done = 0;
            return;
        }
        if(map_menu==2) {
            stage2 = 0;
            dirx = true;
            diry = false;
            chick.life = 200;
            chick.x = WIDTH/2;
            chick.y = 400;
            spider.life = 150;
            bat.life = 250;
            ghost.life = 350;
            bullet_ctrl = 0;
            count_bullet = 0;
            count_corn = 0;
            count_gift = 0;
            gift_state = 0;
            gift_timer = 0;
            loading();
            window = 4;
            map_menu_done = 0;
            return;
        }
    }
}

void window3_update(){
    int i;
    //bullet
    bullet_ctrl++;
    //update enemy position
    if(stage1==0){
        if(bee.life>0){
            if(bee.x>250) dirx = false;
            else if(bee.x<-50) dirx = true;
            if(dirx) bee.x+=2;
            else bee.x-=2;
            if(bullet_ctrl%30==0){
                count_bullet++;
                bullet[count_bullet].life = 1;
                bullet[count_bullet].x = bee.x+100;
                bullet[count_bullet].y = bee.y+100;
            }
            for(i=0; i<count_bullet; i++){
                if(bullet[i].x<WIDTH && bullet[i].x>0 && bullet[i].y<HEIGHT && bullet[i].y>0 && bullet[i].life){
                    if(bullet[i].x<chick.x+150 && bullet[i].x>chick.x+50 && bullet[i].y>chick.y+60 && bullet[i].y<chick.y+100){
                        bullet[i].life = 0;
                        chick.life -= 5;
                    }else bullet[i].y += 3;
                }else bullet[i].life = 0;
            }
        }
    }else if(stage1==1){
        if(queen.life>0){
            if(queen.x>250) dirx = false;
            else if(queen.x<-50) dirx = true;
            if(dirx) queen.x += 4;
            else queen.x -= 4;
            if(bullet_ctrl%20==0){
                count_bullet++;
                bullet[count_bullet].life = 1;
                bullet[count_bullet].x = queen.x+150;
                bullet[count_bullet].y = queen.y+150;
            }
            for(i=0; i<count_bullet; i++){
                if(bullet[i].x<WIDTH && bullet[i].x>0 && bullet[i].y<HEIGHT && bullet[i].y>0 && bullet[i].life){
                    if(bullet[i].x<chick.x+150 && bullet[i].x>chick.x+50 && bullet[i].y>chick.y+60 && bullet[i].y<chick.y+100){
                        bullet[i].life = 0;
                        chick.life -= 10;
                    }else bullet[i].y += 4;
                }else bullet[i].life = 0;
            }
        }else stage1 = WIN;
    }
    //shoot
    if(key_state[ALLEGRO_KEY_SPACE] && pause){
            count_corn++;
            corn[count_corn].life = 1;
            corn[count_corn].x = chick.x+100;
            corn[count_corn].y = chick.y+100;
            pause = false;
    }
    for(i=0; i<count_corn; i++){
        if(corn[i].x<WIDTH && corn[i].x>0 && corn[i].y<HEIGHT && corn[i].y>0 && corn[i].life){
            if(stage1==0){
                if(corn[i].x<bee.x+150 && corn[i].x>bee.x+50 && corn[i].y>bee.y && corn[i].y<bee.y+150){
                    corn[i].life = 0;
                    bee.life -= 100;
                    if(gift_state==1) bee.life -= 10;
                    if(gift_state==2) bee.life -= 10;
                }
            }else if(stage1==1){
                if(corn[i].x<queen.x+150 && corn[i].x>queen.x+50 && corn[i].y>queen.y && corn[i].y<queen.y+150){
                    corn[i].life = 0;
                    queen.life -= 5;
                    if(gift_state==1) queen.life -= 5;
                    if(gift_state==2) queen.life -= 10;
                }
            }
            corn[i].y -= 3;
        }else{
            corn[i].life = 0;
        }
    }
    //gift
    if(bullet_ctrl%150==0){
        count_gift++;
        gift[count_gift].life = 1;
        gift[count_gift].x = rand()%300;
        gift[count_gift].y = 0;
    }
    for(i=0; i<count_gift; i++){
        if(gift[i].x<WIDTH && gift[i].x>0 && gift[i].y<HEIGHT && gift[i].y>=0 && gift[i].life){
            if(gift[i].x<chick.x+150 && gift[i].x>chick.x-50 && gift[i].y>chick.y-20 && gift[i].y<chick.y){
                gift[i].life = 0;
                gift_state = i%3;
                gift_timer = 300;
            }else gift[i].y += 2;
        }else gift[i].life = 0;
    }
    if(gift_state==3 && gift_timer==100) chick.life += 20;
    gift_timer--;
    if(gift_timer==0) gift_state = 0;
    //update chick position
    int vx, vy;
    vx = vy = 0;
    if(key_state[ALLEGRO_KEY_UP] && chick.y>=-100) vy -= 2;
    if(key_state[ALLEGRO_KEY_DOWN] && chick.y<=HEIGHT-200) vy += 2;
    if(key_state[ALLEGRO_KEY_LEFT] && chick.x>=-100) vx -= 2;
    if(key_state[ALLEGRO_KEY_RIGHT] && chick.x<=WIDTH-100) vx += 2;
    chick.x += vx*(vy ? 0.71f : 1);
    chick.y += vy*(vx ? 0.71f : 1);
    if(chick.life<0) stage1 = LOSE;
}
void window3_draw(){
    /*game*/
    //draw image
    al_draw_bitmap(background3, 0, 0, 0);
    int i;
    if(stage1==0){//bee
        if(bee.life>0){
            if(bee.x%20) al_draw_bitmap(bee.image_path1, bee.x, bee.y, 0);
            else al_draw_bitmap(bee.image_path2, bee.x, bee.y, 0);
            al_draw_textf(font, al_map_rgb(255,255,255), bee.x+100, bee.y+150, 0, "HP %i", bee.life);
            //bullet
            for(i=0; i<count_bullet; i++){
                if(bullet[i].life) al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, al_map_rgb(64,64,64));
            }
        }else stage1 = 1;
    }else if(stage1==1){//queen bee
        if(queen.life>0){
            if(queen.x%20) al_draw_bitmap(queen.image_path1, queen.x, queen.y, 0);
            else al_draw_bitmap(queen.image_path2, queen.x, queen.y, 0);
            al_draw_textf(font, al_map_rgb(255,255,255), queen.x+100, queen.y+150, 0, "HP %i", queen.life);
            for(i=0; i<count_bullet; i++){
                if(bullet[i].life) al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, al_map_rgb(64,64,64));
            }
        }else stage1 = WIN;
    }else if(stage1==WIN){
        al_draw_bitmap(win, 0, 0, 0);
        al_flip_display();
        al_rest(3);
        mapunlock = 1;
        window = 2;
        map_menu_done = 0;
        return;
    }else if(stage1==LOSE){
        al_draw_bitmap(lose, 0, 0, 0);
        al_flip_display();
        al_rest(3);
        window = 2;
        map_menu_done = 0;
        return;
    }
    //shoot
    for(i=0; i<count_corn; i++){
        if(corn[i].life){
            al_draw_filled_circle(corn[i].x, corn[i].y, 3, al_map_rgb(255,235,0));
            if(gift_state==1 && gift_timer>0) al_draw_filled_circle(corn[i].x+10, corn[i].y, 3, al_map_rgb(255,235,0));
            if(gift_state==2 && gift_timer>0){
                al_draw_filled_circle(corn[i].x-100, corn[i].y, 2, al_map_rgb(255,255,255));
                al_draw_filled_circle(corn[i].x+125, corn[i].y, 2, al_map_rgb(255,255,255));
            }
        }
    }
    //gift
    for(i=0; i<count_gift; i++){
        if(gift[i].life) al_draw_bitmap(gift0, gift[i].x, gift[i].y, 0);
    }
    //life
    al_draw_textf(font, al_map_rgb(255,255,255), 110, 570, 0, "HP: %i", chick.life);
    if(chick.life/20==5) al_draw_bitmap(life5, 0, 570, 0);
    else if(chick.life/20==4) al_draw_bitmap(life4, 0, 570, 0);
    else if(chick.life/20==3) al_draw_bitmap(life3, 0, 570, 0);
    else if(chick.life/20==2) al_draw_bitmap(life2, 0, 570, 0);
    else if(chick.life/20==1) al_draw_bitmap(life1, 0, 570, 0);
    else al_draw_bitmap(life0, 0, 570, 0);
    //move chick
    if(key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_UP]){
        al_draw_bitmap(chick.image_path1, chick.x, chick.y, 0);
        if(gift_state==2 && gift_timer>0) al_draw_bitmap(friend1, chick.x-50, chick.y, 0);
    }else{
        al_draw_bitmap(chick.image_path2, chick.x, chick.y, 0);
        if(gift_state==2 && gift_timer>0) al_draw_bitmap(friend2, chick.x-50, chick.y, 0);
    }
    al_flip_display();
}

void window4_update(){
    int i;
    //bullet
    bullet_ctrl++;
    //update enemy position
    if(stage2==0){ //spider
        if(spider.life>0){
            if(spider.x>250) dirx = false;
            else if(spider.x<-50) dirx = true;
            if(dirx) spider.x+=2;
            else spider.x-=2;
            /*if(spider.y<0) diry = false;
            else if(spider.y>10) diry = true;
            if(diry) spider.y -= 1;
            else spider.y += 1;*/
            if(bullet_ctrl%30==0){
                count_bullet++;
                bullet[count_bullet].life = 1;
                bullet[count_bullet].x = spider.x+100;
                bullet[count_bullet].y = spider.y+150;
            }
            for(i=0; i<count_bullet; i++){
                if(bullet[i].x<WIDTH && bullet[i].x>0 && bullet[i].y<HEIGHT && bullet[i].y>0 && bullet[i].life){
                    if(bullet[i].x<chick.x+150 && bullet[i].x>chick.x+50 && bullet[i].y>chick.y+60 && bullet[i].y<chick.y+100){
                        bullet[i].life = 0;
                        chick.life -= 15;
                    }else bullet[i].y += 3;
                }else bullet[i].life = 0;
            }
        }
    }else if(stage2==1){ //bat
        if(bat.life>0){
            if(bat.x>250) dirx = false;
            else if(bat.x<-50) dirx = true;
            if(dirx) bat.x += 4;
            else bat.x -= 4;
            /*if(bat.y<0) diry = false;
            else if(bat.y>30) diry = true;
            if(diry) bat.y -= 3;
            else bat.y += 3;*/
            if(bullet_ctrl%20==0){
                count_bullet++;
                bullet[count_bullet].life = 1;
                bullet[count_bullet].x = bat.x+150;
                bullet[count_bullet].y = bat.y+150;
            }
            for(i=0; i<count_bullet; i++){
                if(bullet[i].x<WIDTH && bullet[i].x>0 && bullet[i].y<HEIGHT && bullet[i].y>0 && bullet[i].life){
                    if(bullet[i].x<chick.x+150 && bullet[i].x>chick.x+50 && bullet[i].y>chick.y+60 && bullet[i].y<chick.y+100){
                        bullet[i].life = 0;
                        chick.life -= 15;
                    }else bullet[i].y += 4;
                }else bullet[i].life = 0;
            }
        }
    }else if(stage2==2){ //ghost
            if(ghost.life>0){
                if(ghost.x>250) dirx = false;
                else if(ghost.x<-50) dirx = true;
                if(dirx) ghost.x += 1;
                else ghost.x -= 1;
                if(ghost.y<0) diry = false;
                else if(ghost.y>50) diry = true;
                if(diry) ghost.y -= 2;
                else ghost.y += 2;
                if(bullet_ctrl%20==0){
                    count_bullet++;
                    bullet[count_bullet].life = 1;
                    bullet[count_bullet].x = ghost.x+150;
                    bullet[count_bullet].y = ghost.y+150;
                }
                for(i=0; i<count_bullet; i++){
                    if(bullet[i].x<WIDTH && bullet[i].x>0 && bullet[i].y<HEIGHT && bullet[i].y>0 && bullet[i].life){
                        if(bullet[i].x<chick.x+150 && bullet[i].x>chick.x+50 && bullet[i].y>chick.y+60 && bullet[i].y<chick.y+150){
                            bullet[i].life = 0;
                            chick.life -= 15;
                        }else bullet[i].y += 4;
                    }else bullet[i].life = 0;
                }
            }else stage2 = WIN;
        }
    //shoot
    if(key_state[ALLEGRO_KEY_SPACE] && pause){
            count_corn++;
            corn[count_corn].life = 1;
            corn[count_corn].x = chick.x+100;
            corn[count_corn].y = chick.y+100;
            pause = false;
    }
    for(i=0; i<count_corn; i++){
        if(corn[i].x<WIDTH && corn[i].x>0 && corn[i].y<HEIGHT && corn[i].y>0 && corn[i].life){
            if(stage2==0){
                if(corn[i].x<spider.x+150 && corn[i].x>spider.x+50 && corn[i].y>spider.y && corn[i].y<spider.y+150){
                    corn[i].life = 0;
                    spider.life -= 15;
                    if(gift_state==1) spider.life -= 15;
                    if(gift_state==2) spider.life -= 10;
                }
            }else if(stage2==1){
                if(corn[i].x<bat.x+150 && corn[i].x>bat.x+50 && corn[i].y>bat.y && corn[i].y<bat.y+150){
                    corn[i].life = 0;
                    bat.life -= 10;
                    if(gift_state==1) bat.life -= 10;
                    if(gift_state==2) bat.life -= 10;
                }
            }else if(stage2==2){
                if(corn[i].x<ghost.x+150 && corn[i].x>ghost.x+50 && corn[i].y>ghost.y && corn[i].y<ghost.y+150){
                    corn[i].life = 0;
                    ghost.life -= 5;
                    if(gift_state==1) ghost.life -= 5;
                    if(gift_state==2) ghost.life -= 10;
                }
            }
            corn[i].y -= 3;
        }else{
            corn[i].life = 0;
        }
    }
    //gift
    if(bullet_ctrl%150==0){
        count_gift++;
        gift[count_gift].life = 1;
        gift[count_gift].x = rand()%300;
        gift[count_gift].y = 0;
    }
    for(i=0; i<count_gift; i++){
        if(gift[i].x<WIDTH && gift[i].x>0 && gift[i].y<HEIGHT && gift[i].y>=0 && gift[i].life){
            if(gift[i].x<chick.x+150 && gift[i].x>chick.x-50 && gift[i].y>chick.y-20 && gift[i].y<chick.y){
                gift[i].life = 0;
                gift_state = i%3;
                gift_timer = 300;
            }else gift[i].y += 2;
        }else gift[i].life = 0;

    }
    if(gift_state==3 && gift_timer==100) chick.life += 20;
    gift_timer--;
    if(gift_timer==0) gift_state = 0;
    //update chick position
    int vx, vy;
    vx = vy = 0;
    if(key_state[ALLEGRO_KEY_UP] && chick.y>=-100) vy -= 2;
    if(key_state[ALLEGRO_KEY_DOWN] && chick.y<=HEIGHT-200) vy += 2;
    if(key_state[ALLEGRO_KEY_LEFT] && chick.x>=-100) vx -= 2;
    if(key_state[ALLEGRO_KEY_RIGHT] && chick.x<=WIDTH-100) vx += 2;
    chick.x += vx*(vy ? 0.71f : 1);
    chick.y += vy*(vx ? 0.71f : 1);
    if(chick.life<0) stage2 = LOSE;
}
void window4_draw(){
    /*game*/
    //draw image
    al_draw_bitmap(background4, 0, 0, 0);
    int i;
    if(stage2==0){ //spider
        if(spider.life>0){
            if(spider.x%20>0 && spider.x%20<10) al_draw_bitmap(spider.image_path1, spider.x, spider.y, 0);
            else al_draw_bitmap(spider.image_path2, spider.x, spider.y, 0);
            al_draw_textf(font, al_map_rgb(255,255,255), spider.x+100, spider.y+150, 0, "HP %i", spider.life);
            //bullet
            for(i=0; i<count_bullet; i++){
                if(bullet[i].life) al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, al_map_rgb(64,64,64));
            }
        }else stage2 = 1;
    }else if(stage2==1){//bat
        if(bat.life>0){
            if(bat.x%30>25 && bat.x%30<29) al_draw_bitmap(bat.image_path1, bat.x, bat.y, 0);
            else al_draw_bitmap(bat.image_path2, bat.x, bat.y, 0);
            al_draw_textf(font, al_map_rgb(255,255,255), bat.x+100, bat.y+150, 0, "HP %i", bat.life);
            for(i=0; i<count_bullet; i++){
                if(bullet[i].life) al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, al_map_rgb(64,64,64));
            }
        }else stage2 = 2;
    }else if(stage2==2){//ghost
        if(ghost.life>0){
            al_draw_bitmap(ghost.image_path1, ghost.x, ghost.y, 0);
            al_draw_textf(font, al_map_rgb(255,255,255), ghost.x+100, ghost.y+150, 0, "HP %i", ghost.life);
            for(i=0; i<count_bullet; i++){
                if(bullet[i].life) al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, al_map_rgb(64,64,64));
            }
        }else stage2 = WIN;
    }else if(stage2==WIN){
        al_draw_bitmap(win, 0, 0, 0);
        al_flip_display();
        al_rest(3);
        loading();
        window = 5;
        return;
    }else if(stage2==LOSE){
        al_draw_bitmap(lose, 0, 0, 0);
        al_flip_display();
        al_rest(3);
        window = 2;
        return;
    }
    //shoot
    for(i=0; i<count_corn; i++){
        if(corn[i].life){
            al_draw_filled_circle(corn[i].x, corn[i].y, 3, al_map_rgb(255,235,0));
            if(gift_state==1 && gift_timer>0) al_draw_filled_circle(corn[i].x+10, corn[i].y, 3, al_map_rgb(255,235,0));
            if(gift_state==2 && gift_timer>0){
                al_draw_filled_circle(corn[i].x-100, corn[i].y, 2, al_map_rgb(255,255,255));
                al_draw_filled_circle(corn[i].x+125, corn[i].y, 2, al_map_rgb(255,255,255));
            }
        }
    }
    //gift
    for(i=0; i<count_gift; i++){
        if(gift[i].life) al_draw_bitmap(gift0, gift[i].x, gift[i].y, 0);
    }
    //life
    al_draw_textf(font, al_map_rgb(255,255,255), 110, 570, 0, "HP: %i", chick.life);
    if(chick.life/40==5) al_draw_bitmap(life5, 0, 570, 0);
    else if(chick.life/40==4) al_draw_bitmap(life4, 0, 570, 0);
    else if(chick.life/40==3) al_draw_bitmap(life3, 0, 570, 0);
    else if(chick.life/40==2) al_draw_bitmap(life2, 0, 570, 0);
    else if(chick.life/40==1) al_draw_bitmap(life1, 0, 570, 0);
    else al_draw_bitmap(life0, 0, 570, 0);
    //move chick
    if(key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_UP]){
        al_draw_bitmap(chick.image_path1, chick.x, chick.y, 0);
        if(gift_state==2 && gift_timer>0) al_draw_bitmap(friend1, chick.x-50, chick.y, 0);
    }else{
        al_draw_bitmap(chick.image_path2, chick.x, chick.y, 0);
        if(gift_state==2 && gift_timer>0) al_draw_bitmap(friend2, chick.x-50, chick.y, 0);
    }
    al_flip_display();
}

void window5_update(){
    al_draw_bitmap(background5, 0, 0, 0);
    al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255,255,255), 0);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220, ALLEGRO_ALIGN_CENTRE, "Press \"enter\" to start");
    al_flip_display();
    if(key_state[ALLEGRO_KEY_ENTER] && pause){
        mapunlock = 2;
        al_stop_timer(update_timer);
    }
}
void window5_draw(){
    if(mapunlock==2){
        al_draw_bitmap(manga9, 0, 0, 0);
        al_flip_display();
        al_rest(1);
        al_draw_bitmap(manga10, 0, 0, 0);
        al_flip_display();
        al_rest(1);
        al_draw_bitmap(manga11, 0, 0, 0);
        al_flip_display();
        al_rest(1);
        al_draw_bitmap(manga12, 0, 0, 0);
        al_flip_display();
        al_rest(3);
        window = 1;
        mapunlock = 2;
        al_start_timer(update_timer);
    }
}

void settings_update(){
    if(settings_menu_done==0){
        if(key_state[ALLEGRO_KEY_DOWN] && pause) {
            settings_menu++;
            pause = false;
        }else if(key_state[ALLEGRO_KEY_UP] && pause && settings_menu>0){
            settings_menu--;
            pause = false;
        }
        if(settings_menu%4==1) {
            if(key_state[ALLEGRO_KEY_ENTER] && pause){
                sound++;
                change_window();
                pause = false;
            }
        }else if(settings_menu%4==3){
            if(key_state[ALLEGRO_KEY_ENTER] && pause) {
                settings_menu_done = 1;
                pause = false;
            }
        }
    }
}
void settings_draw(){
    if(settings_menu_done==0){
        if(settings_menu%4==0 && sound%2==0) al_draw_bitmap(settings0, 0, 0, 0);
        else if(settings_menu%4==1 && sound%2==0) al_draw_bitmap(settings2, 0, 0, 0);
        else if(settings_menu%4==2 && sound%2==0) al_draw_bitmap(settings4, 0, 0, 0);
        else if(settings_menu%4==3 && sound%2==0) al_draw_bitmap(settings6, 0, 0, 0);
        else if(settings_menu%4==0 && sound%2==1) al_draw_bitmap(settings1, 0, 0, 0);
        else if(settings_menu%4==1 && sound%2==1) al_draw_bitmap(settings3, 0, 0, 0);
        else if(settings_menu%4==2 && sound%2==1) al_draw_bitmap(settings5, 0, 0, 0);
        else if(settings_menu%4==3 && sound%2==1) al_draw_bitmap(settings7, 0, 0, 0);
        al_flip_display();
    }else{
        window = 1;
        settings_menu_done = 0;
    }
}

void character_menu_update(){
    if(character_menu_done==0){
        if(key_state[ALLEGRO_KEY_RIGHT] && chick_menu<=4 && pause){
            chick_menu++;
            pause = false;
        }else if(key_state[ALLEGRO_KEY_LEFT] && chick_menu>=1 && pause){
            chick_menu--;
            pause = false;
        }else if(key_state[ALLEGRO_KEY_ENTER] && pause){
            character_menu_done = 1;
            pause = false;
        }
    }else if(character_menu_done==1){
        if(key_state[ALLEGRO_KEY_RIGHT] && rabbit_menu<=4 && pause){
            rabbit_menu++;
            pause = false;
        }else if(key_state[ALLEGRO_KEY_LEFT] && rabbit_menu>=1 && pause){
            rabbit_menu--;
            pause = false;
        }else if(key_state[ALLEGRO_KEY_ENTER] && pause){
            character_menu_done = 2;
            pause = false;
            window = 2;
        }
    }
}
void character_menu_draw(){
    if(character_menu_done==0){
        if(chick_menu==1) al_draw_bitmap(character_menu1, 0, 0, 0);
        else if(chick_menu==2) al_draw_bitmap(character_menu2, 0, 0, 0);
        else if(chick_menu==3) al_draw_bitmap(character_menu3, 0, 0, 0);
        else if(chick_menu==4) al_draw_bitmap(character_menu4, 0, 0, 0);
        al_flip_display();
    }else if(character_menu_done==1){
        if(rabbit_menu==1) al_draw_bitmap(character_menu5, 0, 0, 0);
        else if(rabbit_menu==2) al_draw_bitmap(character_menu6, 0, 0, 0);
        else if(rabbit_menu==3) al_draw_bitmap(character_menu7, 0, 0, 0);
        else if(rabbit_menu==4) al_draw_bitmap(character_menu8, 0, 0, 0);
        al_flip_display();
    }else if(character_menu_done==2){
        al_draw_bitmap(character_menu9, 0, 0, 0);
        if(chick_menu==1){
            chick.image_path1 = al_load_bitmap("run1_left.png");
            chick.image_path2 = al_load_bitmap("run1_left1.png");
        }else if(chick_menu==2){
            chick.image_path1 = al_load_bitmap("run2_left.png");
            chick.image_path2 = al_load_bitmap("run2_left1.png");
        }else if(chick_menu==3){
            chick.image_path1 = al_load_bitmap("run3_left.png");
            chick.image_path2 = al_load_bitmap("run3_left1.png");
        }else if(chick_menu==4){
            chick.image_path1 = al_load_bitmap("run4_left.png");
            chick.image_path2 = al_load_bitmap("run4_left1.png");
        }
        if(rabbit_menu==1){
            rabbit.image_path1 = al_load_bitmap("rabbit1.png");
            rabbit.image_path2 = al_load_bitmap("rabbit1.png");
        }else if(rabbit_menu==2){
            rabbit.image_path1 = al_load_bitmap("rabbit2.png");
            rabbit.image_path2 = al_load_bitmap("rabbit2.png");
        }else if(rabbit_menu==3){
            rabbit.image_path1 = al_load_bitmap("rabbit3.png");
            rabbit.image_path2 = al_load_bitmap("rabbit3.png");
        }else if(rabbit_menu==4){
            rabbit.image_path1 = al_load_bitmap("rabbit4.png");
            rabbit.image_path2 = al_load_bitmap("rabbit4.png");
        }
        if(chick.image_path1==NULL || chick.image_path2==NULL){
            printf("character image not loaded\n");
            show_err_msg(-8);
        }
        character_menu_done = 0;
        al_flip_display();
        al_rest(1);
    }
}

void loading(){
    int i;
    al_stop_timer(update_timer);
    for(i=0; i<3; i++){
        al_draw_bitmap(loading1, 0, 0, 0);
        al_flip_display();
        al_rest(1);
        al_draw_bitmap(loading2, 0, 0, 0);
        al_flip_display();
        al_rest(1);
        al_draw_bitmap(loading3, 0, 0, 0);
        al_flip_display();
        al_rest(1);
    }
    al_start_timer(update_timer);
}
void change_window(){
    if(sound%2==0) al_play_sample(song1, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    else if(sound%2==1) al_stop_samples();
}

void game_destroy(){
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(background0); al_destroy_bitmap(background1);al_destroy_bitmap(background1_1);al_destroy_bitmap(background1_2);al_destroy_bitmap(background1_3);al_destroy_bitmap(background1_4); al_destroy_bitmap(background2);al_destroy_bitmap(background2_1);al_destroy_bitmap(background2_2); al_destroy_bitmap(background3); al_destroy_bitmap(background4); al_destroy_bitmap(background5);
    al_destroy_bitmap(settings0);al_destroy_bitmap(settings1);al_destroy_bitmap(settings2);al_destroy_bitmap(settings3);al_destroy_bitmap(settings4);al_destroy_bitmap(settings5);al_destroy_bitmap(settings6);al_destroy_bitmap(settings7);
    al_destroy_bitmap(character_menu1); al_destroy_bitmap(character_menu2); al_destroy_bitmap(character_menu3); al_destroy_bitmap(character_menu4); al_destroy_bitmap(character_menu5); al_destroy_bitmap(character_menu6); al_destroy_bitmap(character_menu7); al_destroy_bitmap(character_menu8); al_destroy_bitmap(character_menu9);
    al_destroy_bitmap(loading1); al_destroy_bitmap(loading2); al_destroy_bitmap(loading3);
    al_destroy_bitmap(manga1);al_destroy_bitmap(manga2);al_destroy_bitmap(manga3);al_destroy_bitmap(manga4);al_destroy_bitmap(manga5);al_destroy_bitmap(manga6);al_destroy_bitmap(manga7);al_destroy_bitmap(manga8);al_destroy_bitmap(manga9);al_destroy_bitmap(manga10);al_destroy_bitmap(manga11);al_destroy_bitmap(manga12);
    al_destroy_bitmap(chick.image_path1); al_destroy_bitmap(rabbit.image_path1);
    al_destroy_bitmap(chick.image_path2); al_destroy_bitmap(rabbit.image_path2);
    al_destroy_bitmap(Chick1.image_path1); al_destroy_bitmap(Chick2.image_path1); al_destroy_bitmap(Chick3.image_path1); al_destroy_bitmap(Chick4.image_path1);
    al_destroy_bitmap(Rabbit1.image_path1); al_destroy_bitmap(Rabbit2.image_path1); al_destroy_bitmap(Rabbit3.image_path1); al_destroy_bitmap(Rabbit4.image_path1);
    al_destroy_bitmap(Chick1.image_path2); al_destroy_bitmap(Chick2.image_path2); al_destroy_bitmap(Chick3.image_path2); al_destroy_bitmap(Chick4.image_path2);
    al_destroy_bitmap(Rabbit1.image_path2); al_destroy_bitmap(Rabbit2.image_path2); al_destroy_bitmap(Rabbit3.image_path2);  al_destroy_bitmap(Rabbit4.image_path2);
    al_destroy_bitmap(bee.image_path1); al_destroy_bitmap(bee.image_path2); al_destroy_bitmap(queen.image_path1); al_destroy_bitmap(queen.image_path2); al_destroy_bitmap(bat.image_path1); al_destroy_bitmap(bat.image_path2); al_destroy_bitmap(spider.image_path1); al_destroy_bitmap(spider.image_path2); al_destroy_bitmap(ghost.image_path1); al_destroy_bitmap(ghost.image_path2);
    al_destroy_bitmap(win); al_destroy_bitmap(lose);
    al_destroy_bitmap(gift0); al_destroy_bitmap(friend1); al_destroy_bitmap(friend2);
    al_destroy_bitmap(life5); al_destroy_bitmap(life4); al_destroy_bitmap(life3); al_destroy_bitmap(life2); al_destroy_bitmap(life1); al_destroy_bitmap(life0);
    al_destroy_sample(song1);
    al_destroy_timer(update_timer);
    al_destroy_font(font);
}
