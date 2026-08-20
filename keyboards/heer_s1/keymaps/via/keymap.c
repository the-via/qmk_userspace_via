// HEER S1 Macropad — Production Firmware
// 4 layers · VIA customisation · Animated OLED
// Flash:  make heer_s1:via:flash
// VIA:    sideload heer_s1_via.json on usevia.app

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────────────────────
// LAYERS  (WINDOWS shortcuts — Ctrl and the Win key, not Cmd)
//
// This replaces the macOS set the board shipped with during development. Every
// binding below is a Windows one; flashing this onto a Mac gives you very little.
// ─────────────────────────────────────────────────────────────────────────────
enum layers {
    L_DEFAULT = 0,   // Clipboard, media transport, Windows shell
    L_GAMING  = 1,   // Discord, capture, F13-F16 macro keys
    L_EDITING = 2,   // Premiere / DaVinci timeline
    L_SYSTEM  = 3,   // Apps, virtual desktops, window management
};

// Windows has no hotkey that opens a terminal, so this one is a macro: Run
// dialog, then "wt". Needs Windows Terminal on PATH — swap "wt" for "cmd" or
// "powershell" if it is not installed.
//
// QK_KB_0, not SAFE_RANGE. VIA's "customKeycodes" array maps onto QK_KB_0
// upwards, so declaring it there makes this appear in VIA by name. At SAFE_RANGE
// it would show as a raw hex value, and a user who remapped the key could never
// select it again — the one binding on the board they could permanently lose.
enum custom_keycodes {
    KC_TERM = QK_KB_0,
};

// ─────────────────────────────────────────────────────────────────────────────
// KEYMAPS
//
//  Physical grid (top-left origin):
//  [ K00 ][ K01 ][ K02 ][ K03 ]
//  [ K10 ][ K11 ][ K12 ][ K13 ]
//  [ K20 ][ K21 ][ K22 ][ K23 ]
//  [ K30 ][ K31 ][ K32 ][ K33 ]
//
//  The two encoder push-switches lead each LAYOUT() below, left one first. They
//  are matrix keys — rows 4 and 5, one column each — which works because both
//  switch to GND and keyboard.json masks off the columns they do not own.
//
//  NOTE: K33 is no longer a layer key. Every one of the sixteen keys carries an
//  action, so layer changes ride on the LEFT ENCODER PRESS. Being in the matrix
//  makes that press remappable, so a user who clears it from all four layers has
//  to return to usevia.app to reach the other layers again.
// ─────────────────────────────────────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ── L1: DEFAULT — clipboard, media, shell ────────────────────────────────
    //   Copy      Paste     Cut       Undo
    //   Redo      SelectAll Find      Save
    //   Prev      Play      Next      Mute
    //   Snip      Explorer  TaskView  Lock
    [L_DEFAULT] = LAYOUT(
        TO(L_GAMING),     KC_MPLY,     // encoders: next layer · play/pause
        LCTL(KC_C),       LCTL(KC_V),  LCTL(KC_X),   LCTL(KC_Z),
        LCTL(KC_Y),       LCTL(KC_A),  LCTL(KC_F),   LCTL(KC_S),
        KC_MPRV,          KC_MPLY,     KC_MNXT,      KC_MUTE,
        LGUI(LSFT(KC_S)), LGUI(KC_E),  LGUI(KC_TAB), LGUI(KC_L)
    ),

    // ── L2: GAMING — comms, capture, macro keys ──────────────────────────────
    //   DiscMute  DiscDeaf  PTT       DiscOverlay
    //   SteamOvl  Screenshot Record   Replay
    //   GameBar   AltTab    Desktop   TaskMgr
    //   Macro1    Macro2    Macro3    Macro4
    //
    // F13-F16 (and F17 for push-to-talk) exist in the HID spec but on no physical
    // keyboard, so games and Discord bind them with zero chance of collision.
    [L_GAMING] = LAYOUT(
        TO(L_EDITING),    KC_MUTE,          // encoders: next layer · panic mute
        LCTL(LSFT(KC_M)), LCTL(LSFT(KC_D)), KC_F17,           LSFT(KC_GRV),
        LSFT(KC_TAB),     KC_F12,           LGUI(LALT(KC_R)), LGUI(LALT(KC_G)),
        LGUI(KC_G),       LALT(KC_TAB),     LGUI(KC_D),       LCTL(LSFT(KC_ESC)),
        KC_F13,           KC_F14,           KC_F15,           KC_F16
    ),

    // ── L3: EDITING — Premiere / DaVinci timeline ────────────────────────────
    //   Razor     Select    RippleDel Undo
    //   MarkIn    MarkOut   Play      Marker
    //   ZoomIn    ZoomOut   FitTline  Snap
    //   Save      Export    FullScrn  Render
    //
    // Render is Enter, not Ctrl+R as specified: in Premiere Ctrl+R is
    // Speed/Duration and would pop a dialog. Enter renders the in-to-out range.
    //
    // Bare letters on purpose: these are the editors' own single-key tools, so
    // they must arrive unmodified.
    [L_EDITING] = LAYOUT(
        TO(L_SYSTEM), KC_SPC,   // encoders: next layer · play/pause the timeline
        KC_C,       KC_V,       LSFT(KC_DEL), LCTL(KC_Z),
        KC_I,       KC_O,       KC_SPC,       KC_M,
        KC_EQL,     KC_MINS,    LSFT(KC_Z),   KC_S,
        LCTL(KC_S), LCTL(KC_M), KC_GRV,       KC_ENT
    ),

    // ── L4: SYSTEM — apps, desktops, windows ─────────────────────────────────
    //   Browser   Explorer  Terminal  Calc
    //   Desk<-    Desk->    NewDesk   CloseDesk
    //   Settings  Display   TaskMgr   CloseApp
    //   Refresh   MinAll    SnapLeft  SnapRight
    [L_SYSTEM] = LAYOUT(
        TO(L_DEFAULT),       LGUI(KC_D),          // encoders: wrap · show desktop
        KC_WHOM,             KC_MYCM,             KC_TERM,             KC_CALC,
        LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RGHT)), LCTL(LGUI(KC_D)),    LCTL(LGUI(KC_F4)),
        LGUI(KC_I),          LGUI(KC_P),          LCTL(LSFT(KC_ESC)),  LALT(KC_F4),
        KC_F5,               LGUI(KC_M),          LGUI(KC_LEFT),       LGUI(KC_RGHT)
    ),
};

// ─────────────────────────────────────────────────────────────────────────────
// ENCODER ROTATION MAP  (defaults — remappable in VIA)
//   Enc1 (left):   volume, except on EDITING where it scrubs the timeline
//   Enc2 (right):  scroll · brightness · zoom
//
// Zoom is Ctrl+Minus / Ctrl+Equals rather than true Ctrl+Scroll. Modifiers can
// only wrap BASIC keycodes (KC_A..KC_EXSEL, 0x04..0xA4) and the mouse wheel sits
// at 0xD9 — so LCTL(MS_WHLU) compiles but does nothing. Discrete zoom steps work
// everywhere instead.
// ─────────────────────────────────────────────────────────────────────────────
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L_DEFAULT] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(MS_WHLD, MS_WHLU)                // scroll
    },
    [L_GAMING] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_BRID, KC_BRIU)                // brightness
    },
    [L_EDITING] = {
        ENCODER_CCW_CW(KC_LEFT, KC_RGHT),               // frame step
        ENCODER_CCW_CW(LCTL(KC_MINS), LCTL(KC_EQL))     // zoom
    },
    [L_SYSTEM] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(LCTL(KC_MINS), LCTL(KC_EQL))     // zoom
    },
};
#endif

#ifdef VIA_ENABLE
#    include "via.h"
#endif

// ─────────────────────────────────────────────────────────────────────────────
// FORCE VIA TO RELOAD THE KEYMAP ABOVE
//
// With VIA_ENABLE the *live* keymap lives in EEPROM, not in this file. VIA only
// reloads the defaults above when via_eeprom_is_valid() is false — and that
// magic is derived from QMK_BUILDDATE's year/month/day ONLY (quantum/via.c:70).
// So rebuilding on the same day keeps the old EEPROM keymap, and edits to
// keymaps[] above silently do nothing.
//
// Bump KEYMAP_VERSION whenever the defaults above change, to force a reload.
// NOTE: this also clears any customisation made in usevia.app.
//
// 6 = the matrix is 6 rows now (see keyboard.json). Rows 4 and 5 carry the two
// encoder push-switches, which used to be polled outside the matrix entirely.
// Both switch to GND, so each occupies column 0 of its own row and `masked`
// filters the phantom presses off the other three columns.
//
// This bump is REQUIRED: more rows means a wider dynamic keymap, so EEPROM
// written by any earlier build is the wrong shape and must be discarded.
// ─────────────────────────────────────────────────────────────────────────────
#define KEYMAP_VERSION 6

void keyboard_post_init_user(void) {
#ifdef VIA_ENABLE
    if (eeconfig_read_user() != KEYMAP_VERSION) {
        eeconfig_init_via();                     // reload keymaps[] into EEPROM
        eeconfig_update_user(KEYMAP_VERSION);
    }
#endif
}

// ─────────────────────────────────────────────────────────────────────────────
// OLED  (128x64, mounted upside-down on the PCB -> OLED_ROTATION_180)
//
//         HEER S1
//   ---------------------
//   ,--.    # # # #
//   | 1|    # . . #     <- live mirror of the 4x4 matrix;
//   |  |    . . . .        a cell fills while its key is down
//   '--'    # # . .
//          E1 +   E2 -  <- flashes on encoder rotation
//
// The 180 rotation is done by the panel itself (SEGMENT_REMAP + COM_SCAN_INC in
// oled_init), NOT by remapping the framebuffer -- see drivers/oled/oled_driver.c.
// So everything below draws in ordinary top-left-origin coordinates and the
// hardware flips it. OLED_COLUMN_OFFSET stays 2: the SH1106 maps RAM column n to
// segment 131-n when remapped, so the 2-column inset is symmetric.
//
// Nothing is redrawn on a timer. The layer digit repaints only when the layer
// changes; the grid repaints only the cells whose state actually flipped; the
// encoder line repaints only when a symbol changes. An idle board therefore
// pushes nothing over I2C at all, which is what keeps this SH1106 happy. See
// config.h for why a full-frame redraw must never return.
// ─────────────────────────────────────────────────────────────────────────────
#ifdef OLED_ENABLE

// ── Key-matrix mirror ────────────────────────────────────────────────────────
// A 4x4 grid mirroring the physical keys. A cell fills while its key is held and
// stays lit at least KEY_LINGER_MS so a quick tap is still visible at 30fps.
//
// Cells are addressed by MATRIX POSITION, never by keycode. That is deliberate:
// the layers are built to be remapped in VIA, so a keycode tells you nothing
// about which key was struck — but (row, col) is fixed by the PCB and always
// points at the same physical switch.
#define GRID_X       75            // digit box and grid centred as a pair: 10..116
#define GRID_Y       16            // vertically centred: 42px of grid in the 53px below the rule
#define GRID_CELL     9            // square, sharp-cornered
#define GRID_GAP      2
#define GRID_PITCH   (GRID_CELL + GRID_GAP)
#define GRID_MID     (GRID_CELL / 2)
#define GRID_SPAN    (4 * GRID_CELL + 3 * GRID_GAP)

// ── Press animation ──────────────────────────────────────────────────────────
// Modelled on the macropad-display mockup: a keycap that DEPRESSES and lights
// its border while held, plus a ripple that fires once outward from the point of
// contact. Two separate things — the hold is a state, the ripple is an event —
// which is why they are tracked separately below rather than as one level ramp.
//
// What did not survive the translation, and why:
//
//   gradients / glow / scanlines   1 bit per pixel. There is no dim, so a glow
//                                  becomes a thicker border and that is all it
//                                  can become.
//   falling ember particles        Built, then removed on request. They worked,
//                                  but a 1-bit framebuffer has no layers, so each
//                                  particle had to recompute and restore the
//                                  keycap pixel it passed over — a lot of
//                                  machinery for something that read as noise
//                                  against the caps.
//   sub-pixel transforms           No fractional coordinates. A press is drawn as
//                                  the cap landing on its shadow instead.
#define RIPPLE_STEP_MS 45
#define RIPPLE_MAX      1          // the strike, and nothing after it
#define KEY_LINGER_MS  60          // holds the depressed cap through a fast tap

// There used to be expanding rings here, r = 1..3 inside the cell. They were a
// dozen pixels moving over 135ms in a 9px box: real in the firmware, invisible on
// the glass. Cut. The cap dropping onto its shadow carries the press now, and the
// neighbours shoving outward carry the motion.


// Held/linger state, one bit per cell, indexed row * 4 + col.
//
// key_linger is tracked as its own mask rather than deriving the linger purely
// from key_since[]. timer_elapsed wraps every ~65s, so a cell that had never been
// pressed would spuriously read "recently pressed" once per wrap and flash.
static uint16_t key_held   = 0;
static uint16_t key_linger = 0;
static uint16_t key_since[16];
static uint8_t  cell_ripple[16];   // 0 = none, 1 = the strike (RIPPLE_MAX is 1)
static uint16_t cell_step_t[16];   // when this cell's ripple last advanced
// Nudge: the eight keys around a press shove outward by a pixel and settle back,
// the way the mockup animates its neighbours. Held per cell as a draw offset so a
// nudged key is simply painted one pixel over — no separate animation path.
//
// One pixel is the entire budget. The gutter between cells is GRID_GAP (2), so a
// 1px shove leaves a pixel of air; 2px and adjacent caps would touch.
// ── Two-layer keycap ─────────────────────────────────────────────────────────
// The cap sits CAP_DROP above and left of its own hard shadow. Pressing moves the
// cap down onto the shadow so the two outlines land exactly on top of each other
// and read as one — the button has bottomed out.
//
// CAP_S + CAP_DROP == GRID_CELL is not a coincidence: the raised cap and its
// shadow together fill the cell slot exactly, so the 2px gutter survives and
// adjacent keys never touch.
#define CAP_DROP  2
#define CAP_S    (GRID_CELL - CAP_DROP)

#define NUDGE_MS 110
static int8_t   cell_ox[16];
static int8_t   cell_oy[16];
static uint16_t nudge_t[16];
static bool     nudged[16];

static uint8_t  cell_drawn[16];    // packed (held << 7 | ripple), to spot changes

// ── Encoder view ─────────────────────────────────────────────────────────────
// Turning either encoder takes over the right-hand panel with a rotating
// sunburst: eleven blades converging to a point, easing round toward wherever
// the detents have pushed it, reaching further out for a moment on each click.
//
// An encoder is a RELATIVE device. It reports "one click clockwise", never a
// position. So there is nothing absolute to display and nothing is displayed:
// the mark wraps freely, with no start and no end, which is the honest shape
// for a control that cannot run out of travel.
//
// The centre is picked against the block grid, not by eye. What matters is the
// CLEAR BOX, which is BURST_MAX_R + 2 each way, not the mark itself: at 84,36
// it spans x 64..103 and y 16..55, two block columns by five pages, so ten
// blocks. Unlike a stepped spinner this repaints EVERY frame while it is up,
// because the easing, the bloom decay and the envelope are all continuous.

// Geometry in Q8 pixels (256 == 1 px).
#define BURST_CX          90    // centre of the right panel (53..127)
#define BURST_CY          33    // centred between the rule (y10) and the label (y56)
#define BURST_RAYS        11
#define BURST_R_IN_Q8    443    // 1.73 px — the blades nearly meet, no hub
#define BURST_R_OUT_Q8  3545    // 13.85 px
#define BURST_BLOOM_Q8  1063    // +4.15 px on a fresh detent
#define BURST_TIP_Q8     461    // 1.80 px half-width at the tip
#define BURST_MAX_R       18    // R_OUT + BLOOM, for the clear box
#define BURST_BOX        (2 * BURST_MAX_R + 4)

#define BURST_STEP      1820    // 10 degrees per detent; 65536 == 360

// Envelope, in milliseconds. Nothing is frame-counted: every rate is
// per-millisecond, so a slow frame moves the animation further rather than
// slowing it down, and the gesture takes the same time whatever the panel does.
#define BURST_GROW_MS    455
#define BURST_HOLD_MS   1250    // grow + full, measured from the last detent
#define BURST_FADE_MS    568
#define BURST_LIFE_MS   (BURST_HOLD_MS + BURST_FADE_MS)
#define BURST_EASE_MS     67    // time constant of the rotation easing

// "E1" / "E2", centred under the mark. Row 7 is y 56..63 — page 7, which the
// mark's clear box never reaches — so it is painted once when the view opens
// and left alone while the mark animates. Free per frame.
//
// It names the KNOB, not the function: the encoder map lives in VIA's EEPROM
// and is remappable, so a hardcoded "VOL" would start lying the moment someone
// changed it in usevia.app. "E1" is a fact about the PCB.
#define ENC_LBL_COL   14        // 14 * 6px = x 84, so "E1" centres on BURST_CX
#define ENC_LBL_ROW    7

// Blade lengths, Q8. The mark's arms are not all the same length, and that
// unevenness is most of what stops it reading as a machine part.
static const uint16_t burst_len[BURST_RAYS] = {
    256, 238, 256, 223, 251, 256, 230, 256, 246, 228, 256
};

// Quarter-wave sine, Q12, 65 entries. Interpolated below, so the angle is
// effectively continuous — a stepped table would make the easing judder.
// Integer-only: the RP2040 has no FPU.
static const int16_t burst_sin_q[65] = {
        0,   101,   201,   301,   401,   501,   601,   700,
      799,   897,   995,  1092,  1189,  1285,  1380,  1474,
     1567,  1660,  1751,  1842,  1931,  2019,  2106,  2191,
     2276,  2359,  2440,  2520,  2598,  2675,  2751,  2824,
     2896,  2967,  3035,  3102,  3166,  3229,  3290,  3349,
     3406,  3461,  3513,  3564,  3612,  3659,  3703,  3745,
     3784,  3822,  3857,  3889,  3920,  3948,  3973,  3996,
     4017,  4036,  4052,  4065,  4076,  4085,  4091,  4095,
     4096
};

static int32_t burst_sin_raw(uint16_t idx) {
    const uint16_t sub = idx & 63u;
    switch ((idx >> 6) & 3u) {
        case 0:  return  burst_sin_q[sub];
        case 1:  return  burst_sin_q[64 - sub];
        case 2:  return -burst_sin_q[sub];
        default: return -burst_sin_q[64 - sub];
    }
}

// phase: 0..65535 == 0..2pi. Returns Q12, -4096..4096.
static int32_t burst_isin(uint16_t phase) {
    const uint16_t idx  = (uint16_t)(phase >> 8);
    const int32_t  frac = phase & 0xFF;
    const int32_t  a    = burst_sin_raw(idx);
    const int32_t  b    = burst_sin_raw((uint16_t)(idx + 1));
    return a + (((b - a) * frac) >> 8);
}

#define BURST_ICOS(p) burst_isin((uint16_t)((p) + 16384u))

// The whole right-hand panel, cleared when swapping between the two views.
// Must start clear of the digit box, or the panel wipe eats its right-hand
// corner brackets. Tied to BOX_X2 so the two can no longer drift apart — the
// bug this fixes was PANEL_X staying at 44 while the box moved right to 51.
#define PANEL_X  (BOX_X2 + 2)
#define PANEL_Y  12
#define PANEL_W  (OLED_DISPLAY_WIDTH - PANEL_X)
#define PANEL_H  (OLED_DISPLAY_HEIGHT - PANEL_Y)

static int32_t  burst_angle  = 0;      // eased, 65536 == 360 degrees
static int32_t  burst_target = 0;      // where the detents have pushed it
static uint16_t burst_bloom  = 0;      // Q8, 256 on a fresh detent
static uint16_t burst_frame  = 0;      // last frame's timestamp, for dt
static uint8_t  enc_which    = 0;      // which knob moved last
static uint8_t  enc_lbl      = 0xFF;   // last label painted
static bool     enc_view     = false;
static bool     view_drawn   = false;
static uint16_t enc_wake_t   = 0;      // when this gesture began, for the grow-in
static uint16_t enc_view_t   = 0;      // last detent, for the hold and the fade

// Corner-bracket frame around the big digit.
#define BOX_X1 10
#define BOX_Y1 13
#define BOX_X2 51
#define BOX_Y2 61
#define BOX_CORNER 8

// Numeral cell, centred inside the frame.
#define DIG_X 18
#define DIG_Y 18
#define DIG_W 26
#define DIG_H 38
#define DIG_R  2           // terminal rounding

// LAYER_BASE decides what the screen calls layer 0. 1 gives the 1-4 numbering a
// product wants; 0 matches what usevia.app shows, which is what a customer sees
// while remapping. They disagree by exactly this constant — change the one value
// to swap the whole scheme.
#define LAYER_BASE 1

// Rounded-stroke numerals, replacing the seven-segment set. Segments with square
// ends and visible gaps read as a calculator readout; continuous strokes with
// rounded terminals read as type, and match the rounded-rectangle language the
// logo is built from.
//
// Coordinates are relative to the DIG_W x DIG_H cell. Strokes overlap at the
// joins on purpose — that is what makes them one letterform instead of segments.
typedef struct { uint8_t x, y, w, h; } dig_stroke_t;

static const dig_stroke_t dig_1[] = {
    {10,  0,  6, 38},                                   // stem
    { 2, 32, 22,  6},                                   // foot
};                                                      // + a swept flag, below
static const dig_stroke_t dig_2[] = {
    { 0,  0, 26,  6}, {20,  4,  6, 16}, { 0, 16, 26,  6},
    { 0, 20,  6, 16}, { 0, 32, 26,  6},
};
static const dig_stroke_t dig_3[] = {
    { 0,  0, 26,  6}, {20,  4,  6, 16}, { 6, 16, 20,  6},
    {20, 20,  6, 16}, { 0, 32, 26,  6},
};
static const dig_stroke_t dig_4[] = {
    { 0,  0,  6, 22}, { 0, 16, 26,  6}, {20,  0,  6, 38},
};

static const dig_stroke_t *const dig_set[4] = {dig_1, dig_2, dig_3, dig_4};
static const uint8_t             dig_len[4] = {2, 5, 5, 3};

// Both are defined further down, next to the logo they were written for.
static void fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool on);
static void draw_rrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r);

// Only the "1" carries a diagonal, so it is the only numeral that needs the
// swept renderer below.
static const bool dig_flag[4] = {true, false, false, false};

// The flag off the top of the "1" stem. A rect table cannot express a diagonal,
// so it is swept: one horizontal run per scanline, reaching further left as it
// descends.
//
// Each run is drawn from its leading edge ALL THE WAY BACK to the stem, not as a
// fixed-width bar sliding left. A sliding bar detaches: it travels 8px while
// being only 6px wide, so below the sixth row it separates from the stem and the
// numeral breaks into two pieces. Filling back to the stem makes it one wedge,
// connected at every row by construction.
#define FLAG_X0 10          // the stem's left edge — where the wedge anchors
#define FLAG_X1  2          // how far left the flag reaches at its foot
#define FLAG_H  11
static void draw_dig_flag(void) {
    for (uint8_t i = 0; i < FLAG_H; i++) {
        const uint8_t x = (uint8_t)(FLAG_X0 -
                          ((uint16_t)(FLAG_X0 - FLAG_X1) * i) / (FLAG_H - 1));
        fill_rect(DIG_X + x, DIG_Y + i, (uint8_t)(FLAG_X0 - x + 1), 1, true);
    }
}


static void fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool on) {
    for (uint8_t i = 0; i < w; i++) {
        for (uint8_t j = 0; j < h; j++) {
            oled_write_pixel(x + i, y + j, on);
        }
    }
}

static void draw_corners(void) {
    const uint8_t n = BOX_CORNER;
    fill_rect(BOX_X1, BOX_Y1, n, 1, true);              // top-left
    fill_rect(BOX_X1, BOX_Y1, 1, n, true);
    fill_rect(BOX_X2 - n + 1, BOX_Y1, n, 1, true);      // top-right
    fill_rect(BOX_X2, BOX_Y1, 1, n, true);
    fill_rect(BOX_X1, BOX_Y2, n, 1, true);              // bottom-left
    fill_rect(BOX_X1, BOX_Y2 - n + 1, 1, n, true);
    fill_rect(BOX_X2 - n + 1, BOX_Y2, n, 1, true);      // bottom-right
    fill_rect(BOX_X2, BOX_Y2 - n + 1, 1, n, true);
}

// `layer` is 0-3; what gets drawn is layer + LAYER_BASE.
static void draw_big_digit(uint8_t layer) {
    fill_rect(DIG_X, DIG_Y, DIG_W, DIG_H, false);       // erase the previous numeral

    const dig_stroke_t *st = dig_set[layer];
    for (uint8_t i = 0; i < dig_len[layer]; i++) {
        draw_rrect(DIG_X + st[i].x, DIG_Y + st[i].y, st[i].w, st[i].h, DIG_R);
    }
    if (dig_flag[layer]) draw_dig_flag();
}

// ── Boot splash: the Heer "H" logo ───────────────────────────────────────────
// Filled rounded rectangle. r is the corner radius; the corner pixels are
// knocked back out after the solid fill.
static void draw_rrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r) {
    fill_rect(x, y, w, h, true);
    for (uint8_t i = 0; i < r; i++) {
        for (uint8_t j = 0; j < r; j++) {
            if (i + j < r) {
                oled_write_pixel(x + i,         y + j,         false);
                oled_write_pixel(x + w - 1 - i, y + j,         false);
                oled_write_pixel(x + i,         y + h - 1 - j, false);
                oled_write_pixel(x + w - 1 - i, y + h - 1 - j, false);
            }
        }
    }
}

// The logo is a stylised "H": a top "U" (two arms rising to the top edge, joined
// along their bottom), two detached blocks below it, and a floating crossbar
// between those (the orange bar in the artwork — this panel is monochrome, so it
// renders white like the rest).
//
// Geometry is taken from icon_original-palette.svg, whose artwork occupies a
// 400x400 square (x and y both run 56..456 inside a 512 viewBox). Every constant
// below is that square mapped onto a 48px box, so the proportions carry over:
//
//     arm width    128/400 -> 15        U height      208/400 -> 25
//     notch depth  144/400 -> 17        block height  160/400 -> 19
//     gap under U   32/400 ->  4        crossbar     108x48   -> 14x6
//
// Centred horizontally: LOGO_X + LOGO_S/2 == 64 == OLED_DISPLAY_WIDTH/2. The box
// sits above the wordmark on row 7, vertically centred in the space that leaves.
#define LOGO_X     40   // (128 - LOGO_S) / 2
#define LOGO_Y      3
#define LOGO_S     48   // square, like the source artwork
#define LOGO_ARM   15   // width of each arm, and of each bottom block
#define LOGO_U_H   25   // height of the top "U"
#define LOGO_NOTCH 17   // depth of the gap between the U's two arms
#define LOGO_BOT_Y 29   // top of the detached bottom blocks
#define LOGO_BOT_H 19
#define LOGO_BAR_X 17   // crossbar, relative to LOGO_X / LOGO_Y
#define LOGO_BAR_Y 29
#define LOGO_BAR_W 14
#define LOGO_BAR_H  6

static void draw_logo(void) {
    // The "U" is one rounded block with the notch cut back out. Drawing an arm +
    // arm + bar as three overlapping rrects instead would leave the bar's own
    // rounded corners bitten into the inside edges of the arms.
    draw_rrect(LOGO_X, LOGO_Y, LOGO_S, LOGO_U_H, 2);
    fill_rect(LOGO_X + LOGO_ARM, LOGO_Y,
              LOGO_S - 2 * LOGO_ARM, LOGO_NOTCH, false);

    draw_rrect(LOGO_X, LOGO_Y + LOGO_BOT_Y, LOGO_ARM, LOGO_BOT_H, 2);
    draw_rrect(LOGO_X + LOGO_S - LOGO_ARM, LOGO_Y + LOGO_BOT_Y,
               LOGO_ARM, LOGO_BOT_H, 2);
    draw_rrect(LOGO_X + LOGO_BAR_X, LOGO_Y + LOGO_BAR_Y,
               LOGO_BAR_W, LOGO_BAR_H, 1);
    oled_set_cursor(7, 7);
    oled_write_P(PSTR("HEER S1"), false);
}

// ── Main-screen painters (split out so the boot transition can force a full
//    repaint, while normal operation only repaints the digit + info block) ────
static void paint_main_chrome(void) {
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("       HEER S1       "), false);
    fill_rect(0, 10, OLED_DISPLAY_WIDTH, 1, true);   // rule under the title
    draw_corners();
}

// Outline with the four corner pixels dropped, so the grid reads as keycaps and
// matches the rounded fill the cell settles into.
// Square outline with the corner pixels dropped, so it reads as a rounded cap.
static void draw_key_outline(uint8_t x, uint8_t y, uint8_t sz) {
    fill_rect(x + 1,          y,             sz - 2, 1,      true);
    fill_rect(x + 1,          y + sz - 1,    sz - 2, 1,      true);
    fill_rect(x,              y + 1,         1,      sz - 2, true);
    fill_rect(x + sz - 1,     y + 1,         1,      sz - 2, true);
}

static void paint_key_cell(uint8_t idx, bool held, uint8_t ripple) {
    const uint8_t bx = GRID_X + (idx % 4) * GRID_PITCH;
    const uint8_t by = GRID_Y + (idx / 4) * GRID_PITCH;

    // Clear a pixel beyond the cap on every side, because a nudged cap is drawn
    // outside its own footprint. One pixel is safe: the gutter is 2.
    fill_rect(bx - 1, by - 1, GRID_CELL + 2, GRID_CELL + 2, false);

    const uint8_t x = (uint8_t)(bx + cell_ox[idx]);
    const uint8_t y = (uint8_t)(by + cell_oy[idx]);

    if (held || ripple == 1) {
        // Bottomed out: the cap has travelled onto its shadow and fills solid.
        // Corners knocked off so it keeps the silhouette it had when raised.
        draw_rrect(x + CAP_DROP, y + CAP_DROP, CAP_S, CAP_S, 1);
        return;
    }

    // Raised. Shadow first, then knock the cap's face out of it so the shadow
    // only shows where it should — down and to the right — and outline the cap
    // on top. Without clearing the face the shadow's far edges would show
    // straight through the cap and the two layers would read as one flat box.
    draw_key_outline(x + CAP_DROP, y + CAP_DROP, CAP_S);
    fill_rect(x, y, CAP_S, CAP_S, false);
    draw_key_outline(x, y, CAP_S);
}

// Shove the eight neighbours of `idx` one pixel directly away from it. Diagonals
// get both components, so the ring pushes outward radially rather than in a cross.
static void nudge_neighbours(uint8_t idx) {
    const int8_t row = (int8_t)(idx / 4);
    const int8_t col = (int8_t)(idx % 4);

    for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            const int8_t r = (int8_t)(row + dy);
            const int8_t c = (int8_t)(col + dx);
            if (r < 0 || r > 3 || c < 0 || c > 3) continue;

            const uint8_t n = (uint8_t)(r * 4 + c);
            cell_ox[n] = dx;
            cell_oy[n] = dy;
            nudge_t[n] = timer_read();
            nudged[n]  = true;
            cell_drawn[n] = 0xFF;                    // force the repaint
        }
    }
}

static void paint_grid(void) {
    for (uint8_t i = 0; i < 16; i++) {
        cell_ripple[i] = 0;
        cell_drawn[i]  = 0;
        cell_ox[i]     = 0;
        cell_oy[i]     = 0;
        nudged[i]      = false;
        paint_key_cell(i, false, 0);
    }
}


// Bresenham. Needed because a blade is a wedge, not a radius: it runs from a
// point near the centre out to a tip BURST_TIP wide, so its edges are not radial.
static void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    int16_t dx = (x1 > x0) ? (int16_t)(x1 - x0) : (int16_t)(x0 - x1);
    int16_t dy = (y1 > y0) ? (int16_t)(y0 - y1) : (int16_t)(y1 - y0);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx + dy;

    for (;;) {
        oled_write_pixel((uint8_t)x0, (uint8_t)y0, true);
        if (x0 == x1 && y0 == y1) break;
        const int16_t e2 = (int16_t)(err * 2);
        if (e2 >= dy) { err = (int16_t)(err + dy); x0 = (int16_t)(x0 + sx); }
        if (e2 <= dx) { err = (int16_t)(err + dx); y0 = (int16_t)(y0 + sy); }
    }
}

// The whole mark at a given size. scale_q8 is the envelope: 0 is nothing, 256
// is full size. Fanning lines from one inner point out to points spread across
// the tip fills each wedge without a polygon scanline fill.
static void paint_burst(int32_t scale_q8) {
    fill_rect(BURST_CX - BURST_MAX_R - 2, BURST_CY - BURST_MAX_R - 2,
              BURST_BOX, BURST_BOX, false);

    const int32_t r_in  = (BURST_R_IN_Q8 * scale_q8) >> 8;
    const int32_t reach = BURST_R_OUT_Q8 + ((BURST_BLOOM_Q8 * (int32_t)burst_bloom) >> 8);
    const int32_t r_out = (reach * scale_q8) >> 8;
    const int32_t tip   = (BURST_TIP_Q8 * scale_q8) >> 8;

    if (r_out <= r_in + 256) return;

    int32_t fan = (tip * 3 + 128) >> 8;
    if (fan < 3) fan = 3;

    const int32_t cx_q8 = (int32_t)BURST_CX << 8;
    const int32_t cy_q8 = (int32_t)BURST_CY << 8;

    for (uint8_t k = 0; k < BURST_RAYS; k++) {
        const uint16_t a  = (uint16_t)(burst_angle + (((int32_t)k * 65536) / BURST_RAYS));
        const int32_t  ca = BURST_ICOS(a);
        const int32_t  sa = burst_isin(a);

        const int16_t ix = (int16_t)((cx_q8 + ((ca * r_in) >> 12) + 128) >> 8);
        const int16_t iy = (int16_t)((cy_q8 + ((sa * r_in) >> 12) + 128) >> 8);

        const int32_t ro    = (r_out * burst_len[k]) >> 8;
        const int32_t ox_q8 = cx_q8 + ((ca * ro) >> 12);
        const int32_t oy_q8 = cy_q8 + ((sa * ro) >> 12);

        const int32_t nx_q8 = (-sa * tip) >> 12;   // perpendicular, fans the tip
        const int32_t ny_q8 = ( ca * tip) >> 12;

        for (int32_t j = 0; j <= fan; j++) {
            const int32_t t = ((j * 512) / fan) - 256;      // Q8, -1.0 .. 1.0
            draw_line(ix, iy,
                      (int16_t)((ox_q8 + ((nx_q8 * t) >> 8) + 128) >> 8),
                      (int16_t)((oy_q8 + ((ny_q8 * t) >> 8) + 128) >> 8));
        }
    }
}

static void paint_enc_label(uint8_t which) {
    char b[3] = "E1";
    b[1] = (char)('1' + which);
    oled_set_cursor(ENC_LBL_COL, ENC_LBL_ROW);
    oled_write(b, false);
}

// Advance the easing and the bloom by however long the last frame actually
// took, then paint. Returns false once the gesture has fully faded out.
//
// The envelope runs on TWO clocks, and that distinction is the whole trick:
//
//   enc_wake_t  when the gesture began   -> drives the grow-in, once
//   enc_view_t  the last detent          -> drives the hold and the fade
//
// Keying the grow-in to the detent instead would restart it on every click, so
// turning the knob at any speed would keep snapping the mark back to nothing
// and regrowing it. Split like this, a continuous turn grows the mark once and
// holds it at full size for as long as detents keep arriving; the fade only
// begins once the knob has actually been still.
static bool paint_enc_view(void) {
    const uint16_t still = timer_elapsed(enc_view_t);   // since the last detent
    if (still >= BURST_LIFE_MS) return false;

    const uint16_t alive = timer_elapsed(enc_wake_t);   // since the gesture began

    // still <= alive always, and BURST_HOLD_MS > BURST_GROW_MS, so these three
    // cases cannot overlap: the fade can never start mid-grow.
    int32_t scale_q8;
    if (alive < BURST_GROW_MS) {
        scale_q8 = ((int32_t)alive * 256) / BURST_GROW_MS;
    } else if (still < BURST_HOLD_MS) {
        scale_q8 = 256;
    } else {
        scale_q8 = 256 - (((int32_t)(still - BURST_HOLD_MS) * 256) / BURST_FADE_MS);
    }
    if (scale_q8 < 0)   scale_q8 = 0;
    if (scale_q8 > 256) scale_q8 = 256;

    uint16_t dt = timer_elapsed(burst_frame);
    burst_frame = timer_read();
    if (dt > 200) dt = 200;                 // a long stall must not overshoot

    int32_t k = ((int32_t)dt * 256) / BURST_EASE_MS;
    if (k > 256) k = 256;
    burst_angle += ((burst_target - burst_angle) * k) >> 8;
    burst_bloom  = (uint16_t)(((int32_t)burst_bloom * (256 - (dt > 256 ? 256 : dt))) >> 8);

    paint_burst(scale_q8);
    return true;
}

// A layer change always lands back on the grid; if the encoder view happened to
// be up, this drops it so the two views cannot both think they own the panel.
static void paint_main_layer(uint8_t cur) {
    draw_big_digit(cur);                             // 0-3, same as usevia.app
    enc_view   = false;
    view_drawn = false;
    enc_lbl    = 0xFF;                               // panel wipe takes the label too
    fill_rect(PANEL_X, PANEL_Y, PANEL_W, PANEL_H, false);
    paint_grid();                                    // resets every cell to idle
}

// Records input state only — the drawing happens in oled_task_user, because
// process_record_user runs inside the matrix scan and pushing I2C traffic from
// here would stall it.
//
// This fires on all 18 keys and on encoder rotation. Only the 16 in the grid
// get an animation — the two encoder presses live on rows 4 and 5, which the
// bounds check below drops.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (record->event.type) {
        case KEY_EVENT: {
            // Guard the bounds: the matrix is 6 rows, and rows 4 and 5 hold the
            // encoder push-switches. They are real keys, but they are not part
            // of the 4x4 grid, so they have no cell to light up.
            const uint8_t r = record->event.key.row;
            const uint8_t c = record->event.key.col;
            if (r < 4 && c < 4) {
                const uint8_t i = r * 4 + c;
                if (record->event.pressed) {
                    key_held    |= (uint16_t)1 << i;
                    key_linger  |= (uint16_t)1 << i;
                    key_since[i] = timer_read();

                    // Fire the ripple from the moment of contact. Re-arming it
                    // unconditionally means a re-press part way through an old
                    // ripple restarts it rather than being swallowed.
                    cell_ripple[i] = 1;
                    cell_step_t[i] = timer_read();
                    nudge_neighbours(i);
                } else {
                    key_held &= ~((uint16_t)1 << i);
                }
            }
            break;
        }

        // With ENCODER_MAP_ENABLE, encoder_update_user is never called — rotation
        // arrives here instead as a synthetic event carrying the encoder index in
        // event.key.col (see quantum/encoder.c, encoder_handle_queue).
        case ENCODER_CW_EVENT:
        case ENCODER_CCW_EVENT:
            if (record->event.pressed && record->event.key.col < 2) {
                // The mark turns the way the knob turns. It wraps freely —
                // there is no start and no end, which is the point: an encoder
                // has no position to run out of.
                //
                // This only moves the TARGET. The mark eases toward it in
                // oled_task_user, so detents arriving faster than a frame pile
                // into one smooth sweep instead of a backlog of steps.
                if (!enc_view) {
                    burst_angle = burst_target;   // snap on wake, don't unwind
                    burst_frame = timer_read();
                    enc_wake_t  = timer_read();   // grow-in starts here, once
                }
                if (record->event.type == ENCODER_CW_EVENT) {
                    burst_target += BURST_STEP;
                } else {
                    burst_target -= BURST_STEP;
                }
                burst_bloom = 256;                // blades reach out, then settle
                enc_which   = record->event.key.col;
                enc_view    = true;
                enc_view_t  = timer_read();
            }
            break;

        default:
            break;
    }

    // Windows exposes no hotkey for "open a terminal", so this is the one binding
    // on the board that has to be typed rather than sent. The delay is not
    // decoration: the Run dialog needs time to take focus, and without it the
    // string lands in whatever was focused before.
    if (keycode == KC_TERM) {
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI("r") SS_DELAY(250) "wt\n");
        }
        return false;
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_set_brightness(OLED_BRIGHTNESS);
    return OLED_ROTATION_180;   // display is mounted upside-down on the PCB
}

// Boot animation: show the logo, hold, then curtain-wipe into the main screen.
// The "effect" rides the driver's own flush behaviour — it repaints one 64-byte
// block per frame, lowest index first, so a whole-buffer swap reveals itself
// top-to-bottom. No per-frame motion (which this SH1106 is too slow to push),
// and no oversized transaction (which would hang the I2C bus — see config.h).
enum boot_phase { BP_LOGO, BP_HOLD, BP_RUN };
#define BOOT_LOGO_MS 1600   // ~0.5s to curtain the logo in + ~1.1s to admire it

bool oled_task_user(void) {
    static uint8_t  phase      = BP_LOGO;
    static uint16_t phase_t    = 0;
    static uint8_t  last_layer = 0xFF;

    switch (phase) {
        case BP_LOGO:                              // paint logo once, let it flush
            oled_clear();
            draw_logo();
            phase_t = timer_read();
            phase   = BP_HOLD;
            return false;

        case BP_HOLD:
            if (timer_elapsed(phase_t) < BOOT_LOGO_MS) return false;
            // Swap the whole buffer to the main screen. oled_clear() marks every
            // block dirty, so the driver wipes the logo away and the main screen
            // in, top-to-bottom, as it flushes.
            oled_clear();
            paint_main_chrome();
            last_layer = get_highest_layer(layer_state) & 3;
            paint_main_layer(last_layer);
            phase = BP_RUN;
            return false;

        case BP_RUN:
        default: {
            const uint8_t cur = get_highest_layer(layer_state) & 3;
            if (cur != last_layer) {               // repaint only on layer change
                last_layer = cur;
                paint_main_layer(cur);
            }

            // Swapping views wipes the right-hand panel, so it only happens on
            // an actual transition — never per frame. The title, the rule and
            // the layer digit all stay put.
            if (enc_view != view_drawn) {
                view_drawn = enc_view;
                fill_rect(PANEL_X, PANEL_Y, PANEL_W, PANEL_H, false);
                if (enc_view) {
                    paint_enc_label(enc_which);   // page 7; the mark never touches it
                    enc_lbl = enc_which;
                } else {
                    paint_grid();
                    enc_lbl = 0xFF;
                }
                return false;
            }

            if (enc_view) {
                // Swapping knobs mid-gesture is the only thing that moves the
                // label, so it repaints on that and nothing else.
                if (enc_which != enc_lbl) {
                    paint_enc_label(enc_which);
                    enc_lbl = enc_which;
                    return false;
                }
                // The mark repaints every frame: the easing, the bloom decay and
                // the grow/fade envelope are all continuous, so there is no
                // "nothing changed" case to skip.
                if (!paint_enc_view()) {
                    enc_view = false;             // faded out; swap back next pass
                }
                return false;
            }

            // Grid view. Two independent things per cell:
            //
            //   held    a STATE — the cap is depressed for exactly as long as
            //           the switch is down (plus KEY_LINGER_MS so a fast tap is
            //           not missed between frames).
            //   ripple  an EVENT — fired once at the moment of contact and
            //           allowed to run out on its own, whether or not the key is
            //           still down. Holding a key does not hold the ripple open,
            //           which is what stops a held key looking like a stuck one.
            //
            // Only cells whose packed state actually changed get repainted.
            for (uint8_t i = 0; i < 16; i++) {
                const uint16_t bit = (uint16_t)1 << i;

                if ((key_linger & bit) && timer_elapsed(key_since[i]) >= KEY_LINGER_MS) {
                    key_linger &= ~bit;
                }
                const bool held = (key_held & bit) || (key_linger & bit);

                if (cell_ripple[i] && timer_elapsed(cell_step_t[i]) >= RIPPLE_STEP_MS) {
                    cell_ripple[i] = (cell_ripple[i] >= RIPPLE_MAX) ? 0 : cell_ripple[i] + 1;
                    cell_step_t[i] = timer_read();
                }

                if (nudged[i] && timer_elapsed(nudge_t[i]) >= NUDGE_MS) {
                    nudged[i]  = false;
                    cell_ox[i] = 0;
                    cell_oy[i] = 0;
                    cell_drawn[i] = 0xFF;            // shoved back, so repaint
                }

                const uint8_t want = (uint8_t)((held ? 0x80 : 0) | cell_ripple[i]);
                if (want == cell_drawn[i]) continue;

                cell_drawn[i] = want;
                paint_key_cell(i, held, cell_ripple[i]);
            }

            return false;
        }
    }
}

#endif // OLED_ENABLE