/* KallistiOS ##version##

Example based on the code posted 
by black aura on  Fri Jul 08, 2005 11:29 am
And example by tonma  Mon Apr 25, 2016 5:28 am
fixed and update for kos2.0 by Ian micheal Sun Oct 2022 11:09pm
Added drawing image from png example kos
Fixed missing "/' and fs_chdir("/romdisk3/");
*/
#include <kos.h>
#include <png/png.h>
#include <zlib/zlib.h>
#include<stdbool.h>
/* textures */

pvr_ptr_t back_tex;

// test mount romdisk en ram 
static bool mount_romdisk(char *filename, char *mountpoint)
{
	void *buffer;
	ssize_t size = fs_load(filename, &buffer);

	printf("Load Romdisk3 %d\n", size);

	if (size != 1)
	{
		fs_romdisk_mount(mountpoint, buffer, 1);
		
		printf("Load Inside Romdisk3 %d\n", size);
		return true;

	} else return false;
}

/* init background */
void back_init() {
    back_tex = pvr_mem_malloc(512 * 512 * 2);
    fs_chdir("/romdisk3/");
    png_to_texture("/romdisk3/background.png", back_tex, PNG_NO_ALPHA);
}

/* draw background */
void draw_back(void) {
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565, 512, 512, back_tex, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 1;
    vert.y = 1;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 1;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 1;
    vert.y = 480;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 480;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

/* draw one frame */
void draw_frame(void) {
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_OP_POLY);
    draw_back();
    pvr_list_finish();
    pvr_list_begin(PVR_LIST_TR_POLY);
    pvr_list_finish();
    pvr_scene_finish();

}

int main(void) {
    int done = 0;

    /* init kos  */
    pvr_init_defaults();
    int resMount = mount_romdisk("/cd/romdisk1.img", "/romdisk3");
     printf("Load Romdisk3 %d\n", resMount);

    /* init background */
    back_init();
    
    /* keep drawing frames until start is pressed */
    while(!done) {
        MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)

        if(st->buttons & CONT_START)
            done = 1;

        MAPLE_FOREACH_END()
      //  printf("after maple end\n");
     
        draw_frame();
    }
      //  printf("after draw frame\n");
      /* Unmount loaded romdisk */
        fs_romdisk_unmount("/romdisk3");
    return 0;
}
