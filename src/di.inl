/*
 * Copyright (c) 2018 naehrwert
 * Copyright (C) 2018 CTCaer
 * Copyright (c) 2020 Spacecraft-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
static const cfg_op_t _car_init_erista[4] = {
	{ 0, 0x4E, 0x40000000 },
	{ 0, 0x34, 0x4830A001 },
	{ 0, 0x36, 0x20 },
	{ 0, 0x37, 0x2D0AAA }
};

static const cfg_op_t _car_init_mariko[4] = {
	{ 0, 0x4E, 0x40000000 },
	{ 0, 0x34, 0x4830A001 },
	{ 0, 0x36, 0 },
	{ 0, 0x37, 0x2DFC00 }
};

static const cfg_op_t _di_init[94] = {
	{ 0, DC_CMD_STATE_ACCESS, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_REG_ACT_CONTROL, 0x54 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_DISP_DC_MCCIF_FIFOCTRL, 0 },
	{ 0, DC_DISP_DISP_MEM_HIGH_PRIORITY, 0 },
	{ 0, DC_DISP_DISP_MEM_HIGH_PRIORITY_TIMER, 0 },
	{ 0, DC_CMD_DISPLAY_POWER_CONTROL, PW0_ENABLE | PW1_ENABLE | PW2_ENABLE | PW3_ENABLE | PW4_ENABLE | PM0_ENABLE | PM1_ENABLE },
	{ 0, DC_CMD_GENERAL_INCR_SYNCPT_CNTRL, SYNCPT_CNTRL_NO_STALL },
	{ 0, DC_CMD_CONT_SYNCPT_VSYNC, SYNCPT_VSYNC_ENABLE | 0x9 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE | WIN_A_UPDATE | WIN_B_UPDATE | WIN_C_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ | WIN_A_ACT_REQ | WIN_B_ACT_REQ | WIN_C_ACT_REQ },
	{ 0, DC_CMD_STATE_ACCESS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_DV_CONTROL, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_CSC_YOF,   0xF0 },
	{ 0, DC_WIN_CSC_KYRGB, 0x12A },
	{ 0, DC_WIN_CSC_KUR,   0 },
	{ 0, DC_WIN_CSC_KVR,   0x198 },
	{ 0, DC_WIN_CSC_KUG,   0x39B },
	{ 0, DC_WIN_CSC_KVG,   0x32F },
	{ 0, DC_WIN_CSC_KUB,   0x204 },
	{ 0, DC_WIN_CSC_KVB,   0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_DV_CONTROL, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_CSC_YOF,   0xF0 },
	{ 0, DC_WIN_CSC_KYRGB, 0x12A },
	{ 0, DC_WIN_CSC_KUR,   0 },
	{ 0, DC_WIN_CSC_KVR,   0x198 },
	{ 0, DC_WIN_CSC_KUG,   0x39B },
	{ 0, DC_WIN_CSC_KVG,   0x32F },
	{ 0, DC_WIN_CSC_KUB,   0x204 },
	{ 0, DC_WIN_CSC_KVB,   0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_DV_CONTROL, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_CSC_YOF,   0xF0 },
	{ 0, DC_WIN_CSC_KYRGB, 0x12A },
	{ 0, DC_WIN_CSC_KUR,   0 },
	{ 0, DC_WIN_CSC_KVR,   0x198 },
	{ 0, DC_WIN_CSC_KUG,   0x39B },
	{ 0, DC_WIN_CSC_KVG,   0x32F },
	{ 0, DC_WIN_CSC_KUB,   0x204 },
	{ 0, DC_WIN_CSC_KVB,   0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_COLOR_CONTROL, BASE_COLOR_SIZE_888 },
	{ 0, DC_DISP_DISP_INTERFACE_CONTROL, DISP_DATA_FORMAT_DF1P1C },
	{ 0, DC_COM_PIN_OUTPUT_POLARITY(1), 0x1000000 },
	{ 0, DC_COM_PIN_OUTPUT_POLARITY(3), 0 },
	{ 0, DC_DISP_BLEND_BACKGROUND_COLOR, 0 },
	{ 0, DC_COM_CRC_CONTROL, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE | WIN_A_UPDATE | WIN_B_UPDATE | WIN_C_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ | WIN_A_ACT_REQ | WIN_B_ACT_REQ | WIN_C_ACT_REQ },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, 0x716, 0x10000FF },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, 0x716, 0x10000FF },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, 0x716, 0x10000FF },
	{ 0, DC_CMD_DISPLAY_COMMAND_OPTION0, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_COMMAND, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE | WIN_A_UPDATE | WIN_B_UPDATE | WIN_C_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ | WIN_A_ACT_REQ | WIN_B_ACT_REQ | WIN_C_ACT_REQ }
};

static const cfg_op_t _dsi_init_p1[8] = {
	{ 0, DSI_WR_DATA, 0 },
	{ 0, DSI_INT_ENABLE, 0 },
	{ 0, DSI_INT_STATUS, 0 },
	{ 0, DSI_INT_MASK, 0 },
	{ 0, DSI_INIT_SEQ_DATA_0, 0 },
	{ 0, DSI_INIT_SEQ_DATA_1, 0 },
	{ 0, DSI_INIT_SEQ_DATA_2, 0 },
	{ 0, DSI_INIT_SEQ_DATA_3, 0 },
};

static const cfg_op_t _dsi_init_p2_mariko[1] = {
	{ 0, DSI_INIT_SEQ_DATA_15, 0 },
};

static const cfg_op_t _dsi_init_p3[14] = {
	{ 0, DSI_DCS_CMDS, 0 },
	{ 0, DSI_PKT_SEQ_0_LO, 0 },
	{ 0, DSI_PKT_SEQ_1_LO, 0 },
	{ 0, DSI_PKT_SEQ_2_LO, 0 },
	{ 0, DSI_PKT_SEQ_3_LO, 0 },
	{ 0, DSI_PKT_SEQ_4_LO, 0 },
	{ 0, DSI_PKT_SEQ_5_LO, 0 },
	{ 0, DSI_PKT_SEQ_0_HI, 0 },
	{ 0, DSI_PKT_SEQ_1_HI, 0 },
	{ 0, DSI_PKT_SEQ_2_HI, 0 },
	{ 0, DSI_PKT_SEQ_3_HI, 0 },
	{ 0, DSI_PKT_SEQ_4_HI, 0 },
	{ 0, DSI_PKT_SEQ_5_HI, 0 },
	{ 0, DSI_CONTROL, 0 },
};

static const cfg_op_t _dsi_init_p4_mariko[7] = {
	{ 0, DSI_PAD_CONTROL_1, 0 },
	{ 0, DSI_PAD_CONTROL_2, 0 },
	{ 0, DSI_PAD_CONTROL_3, 0 },
	{ 0, DSI_PAD_CONTROL_4, 0 },
	{ 0, DSI_PAD_CONTROL_5, 0 },
	{ 0, DSI_PAD_CONTROL_6, 0 },
	{ 0, DSI_PAD_CONTROL_7, 0 },
};

static const cfg_op_t _dsi_init_p5[10] = {
	{ 0, DSI_PAD_CONTROL_CD, 0 },
	{ 0, DSI_SOL_DELAY, 0x18 },
	{ 0, DSI_MAX_THRESHOLD, 0x1E0 },
	{ 0, DSI_TRIGGER, 0 },
	{ 0, DSI_INIT_SEQ_CONTROL, 0 },
	{ 0, DSI_PKT_LEN_0_1, 0 },
	{ 0, DSI_PKT_LEN_2_3, 0 },
	{ 0, DSI_PKT_LEN_4_5, 0 },
	{ 0, DSI_PKT_LEN_6_7, 0 },
	{ 0, DSI_PAD_CONTROL_1, 0 },
};

static const cfg_op_t _dsi_phy_timing_0_erista[1] = {
	{ 0, DSI_PHY_TIMING_0, 0x6070601 },
};

static const cfg_op_t _dsi_phy_timing_0_mariko[1] = {
	{ 0, DSI_PHY_TIMING_0, 0x6070603 },
};

static const cfg_op_t _dsi_init_p7[12] = {
	{ 0, DSI_PHY_TIMING_1, 0x40A0E05 },
	{ 0, DSI_PHY_TIMING_2, 0x30109 },
	{ 0, DSI_BTA_TIMING, 0x190A14 },
	{ 0, DSI_TIMEOUT_0, DSI_TIMEOUT_LRX(0x2000) | DSI_TIMEOUT_HTX(0xFFFF) },
	{ 0, DSI_TIMEOUT_1, DSI_TIMEOUT_PR(0x765) | DSI_TIMEOUT_TA(0x2000) },
	{ 0, DSI_TO_TALLY, 0 },
	{ 0, DSI_PAD_CONTROL, DSI_PAD_CONTROL_VS1_PULLDN(0) | DSI_PAD_CONTROL_VS1_PDIO(0) },
	{ 0, DSI_POWER_CONTROL, DSI_POWER_CONTROL_ENABLE },
	{ 0, DSI_POWER_CONTROL, DSI_POWER_CONTROL_ENABLE },
	{ 0, DSI_POWER_CONTROL, 0 },
	{ 0, DSI_POWER_CONTROL, 0 },
	{ 0, DSI_PAD_CONTROL_1, 0 },
};

static const cfg_op_t _dsi_init_p9[14] = {
	{ 0, DSI_PHY_TIMING_1, 0x40A0E05 },
	{ 0, DSI_PHY_TIMING_2, 0x30118 },
	{ 0, DSI_BTA_TIMING, 0x190A14 },
	{ 0, DSI_TIMEOUT_0, DSI_TIMEOUT_LRX(0x2000) | DSI_TIMEOUT_HTX(0xFFFF) },
	{ 0, DSI_TIMEOUT_1, DSI_TIMEOUT_PR(0x1343) | DSI_TIMEOUT_TA(0x2000) },
	{ 0, DSI_TO_TALLY, 0 },
	{ 0, DSI_HOST_CONTROL, DSI_HOST_CONTROL_CRC_RESET | DSI_HOST_CONTROL_TX_TRIG_HOST | DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC },
	{ 0, DSI_CONTROL, DSI_CONTROL_LANES(3) | DSI_CONTROL_HOST_ENABLE },
	{ 0, DSI_POWER_CONTROL, DSI_POWER_CONTROL_ENABLE },
	{ 0, DSI_POWER_CONTROL, DSI_POWER_CONTROL_ENABLE },
	{ 0, DSI_MAX_THRESHOLD, 0x40 },
	{ 0, DSI_TRIGGER, 0 },
	{ 0, DSI_TX_CRC, 0 },
	{ 0, DSI_INIT_SEQ_CONTROL, 0 }
};

static const cfg_op_t _dsi_jdi_init[48] = {
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0x9483FFB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0xBD15 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x1939 },
	{ 0, DSI_WR_DATA, 0xAAAAAAD8 },
	{ 0, DSI_WR_DATA, 0xAAAAAAEB },
	{ 0, DSI_WR_DATA, 0xAAEBAAAA },
	{ 0, DSI_WR_DATA, 0xAAAAAAAA },
	{ 0, DSI_WR_DATA, 0xAAAAAAEB },
	{ 0, DSI_WR_DATA, 0xAAEBAAAA },
	{ 0, DSI_WR_DATA, 0xAA },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x1BD15 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x2739 },
	{ 0, DSI_WR_DATA, 0xFFFFFFD8 },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFF },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x2BD15 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0xF39 },
	{ 0, DSI_WR_DATA, 0xFFFFFFD8 },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFFFF },
	{ 0, DSI_WR_DATA, 0xFFFFFF },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0xBD15 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x6D915 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0xB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x1105 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 180, 0 },
	{ 0, DSI_WR_DATA, 0x2905 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST }
};

static const cfg_op_t _dsi_innolux_v1_init[14] = {
	{ 0, DSI_WR_DATA, 0x1105 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 180, 0 },
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0x9483FFB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
	{ 0, DSI_WR_DATA, 0x739 },
	{ 0, DSI_WR_DATA, 0x751548B1 },
	{ 0, DSI_WR_DATA, 0x143209 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
	{ 0, DSI_WR_DATA, 0x2905 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST }
};

static const cfg_op_t _dsi_auo_v1_init[14] = {
	{ 0, DSI_WR_DATA, 0x1105 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 180, 0 },
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0x9483FFB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
	{ 0, DSI_WR_DATA, 0x739 },
	{ 0, DSI_WR_DATA, 0x711148B1 },
	{ 0, DSI_WR_DATA, 0x143209 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
	{ 0, DSI_WR_DATA, 0x2905 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST }
};

static const cfg_op_t _dsi_v2_init[5] = {
	{ 0, DSI_WR_DATA, 0x1105 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 120, 0 },
	{ 0, DSI_WR_DATA, 0x2905 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST }
};

static const cfg_op_t _car_init2_erista[3] = {
	{ 0, 0x34, 0x4810C001 },
	{ 0, 0x36, 0x20 },
	{ 0, 0x37, 0x2DFC00 }
};

static const cfg_op_t _car_init2_mariko[3] = {
	{ 0, 0x34, 0x4810C001 },
	{ 0, 0x36, 0 },
	{ 0, 0x37, 0x2DFC00 }
};

static const cfg_op_t _dsi_init2_p1[1] = {
	{ 0, DSI_PAD_CONTROL_1, 0 },
};

static const cfg_op_t _dsi_init2_p3[19] = {
	{ 0, DSI_PHY_TIMING_1, 0x40A0E05 },
	{ 0, DSI_PHY_TIMING_2, 0x30172 },
	{ 0, DSI_BTA_TIMING, 0x190A14 },
	{ 0, DSI_TIMEOUT_0, DSI_TIMEOUT_LRX(0x2000) | DSI_TIMEOUT_HTX(0xA40) },
	{ 0, DSI_TIMEOUT_1, DSI_TIMEOUT_PR(0x5A2F) | DSI_TIMEOUT_TA(0x2000) },
	{ 0, DSI_TO_TALLY, 0 },
	{ 0, DSI_PKT_SEQ_0_LO, 0x40000208 },
	{ 0, DSI_PKT_SEQ_2_LO, 0x40000308 },
	{ 0, DSI_PKT_SEQ_4_LO, 0x40000308 },
	{ 0, DSI_PKT_SEQ_1_LO, 0x40000308 },
	{ 0, DSI_PKT_SEQ_3_LO, 0x3F3B2B08 },
	{ 0, DSI_PKT_SEQ_3_HI, 0x2CC },
	{ 0, DSI_PKT_SEQ_5_LO, 0x3F3B2B08 },
	{ 0, DSI_PKT_SEQ_5_HI, 0x2CC },
	{ 0, DSI_PKT_LEN_0_1, 0xCE0000 },
	{ 0, DSI_PKT_LEN_2_3, 0x87001A2 },
	{ 0, DSI_PKT_LEN_4_5, 0x190 },
	{ 0, DSI_PKT_LEN_6_7, 0x190 },
	{ 0, DSI_HOST_CONTROL, 0 }
};

static const cfg_op_t _dsi_init3[10] = {
	{ 0, DSI_TRIGGER, 0 },
	{ 0, DSI_CONTROL, 0 },
	{ 0, DSI_SOL_DELAY, 6 },
	{ 0, DSI_MAX_THRESHOLD, 0x1E0 },
	{ 0, DSI_POWER_CONTROL, DSI_POWER_CONTROL_ENABLE },
	{ 0, DSI_CONTROL, DSI_CONTROL_HS_CLK_CTRL | DSI_CONTROL_FORMAT(3) | DSI_CONTROL_LANES(3) | DSI_CONTROL_VIDEO_ENABLE },
	{ 0, DSI_HOST_CONTROL, DSI_HOST_CONTROL_HS | DSI_HOST_CONTROL_FIFO_SEL| DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC },
	{ 0, DSI_CONTROL, DSI_CONTROL_HS_CLK_CTRL | DSI_CONTROL_FORMAT(3) | DSI_CONTROL_LANES(3) | DSI_CONTROL_VIDEO_ENABLE },
	{ 0, DSI_HOST_CONTROL, DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC },
	{ 0, DSI_HOST_CONTROL, DSI_HOST_CONTROL_HS | DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC }
};

static const cfg_op_t _mipi_init[4] = {
	{ 0, 0x18, 0 },
	{ 0, 0x02, 0xF3F10000 },
	{ 0, 0x16, 0 },
	{ 0, 0x18, 0 }
};

static const cfg_op_t _mipi_init2_erista[2] = {
	{ 0, 0x18, 0x10010 },
	{ 0, 0x17, 0x300 }
};

static const cfg_op_t _mipi_init2_mariko[2] = {
	{ 0, 0x18, 0x10010 },
	{ 0, 0x17, 0 }
};

static const cfg_op_t _dsi_init4_erista[4] = {
	{ 0, DSI_PAD_CONTROL_1, 0 },
	{ 0, DSI_PAD_CONTROL_2, 0 },
	{ 0, DSI_PAD_CONTROL_3, DSI_PAD_PREEMP_PD_CLK(0x3) | DSI_PAD_PREEMP_PU_CLK(0x3) | DSI_PAD_PREEMP_PD(0x03) | DSI_PAD_PREEMP_PU(0x3) },
	{ 0, DSI_PAD_CONTROL_4, 0 }
};

static const cfg_op_t _dsi_init4_mariko[7] = {
	{ 0, DSI_PAD_CONTROL_1, 0 },
	{ 0, DSI_PAD_CONTROL_2, 0 },
	{ 0, DSI_PAD_CONTROL_3, 0 },
	{ 0, DSI_PAD_CONTROL_4, 0x77777 },
	{ 0, DSI_PAD_CONTROL_5, 0x77777 },
	{ 0, DSI_PAD_CONTROL_6, 0x1111 },
	{ 0, DSI_PAD_CONTROL_7, 0 }
};

static const cfg_op_t _mipi_init3_p1_erista[4] = {
	{ 0, 0xE, 0x200200 },
	{ 0, 0xF, 0x200200 },
	{ 0, 0x19, 0x200002 },
	{ 0, 0x1A, 0x200002 }
};

static const cfg_op_t _mipi_init3_p1_mariko[4] = {
	{ 0, 0xE,  0x200006 },
	{ 0, 0xF, 0x200006 },
	{ 0, 0x19, 0x260000 },
	{ 0, 0x1A, 0x260000 }
};

static const cfg_op_t _mipi_init3_p2[12] = {
	{ 0, 5, 0 },
	{ 0, 6, 0 },
	{ 0, 7, 0 },
	{ 0, 8, 0 },
	{ 0, 9, 0 },
	{ 0, 0xA, 0 },
	{ 0, 0x10, 0 },
	{ 0, 0x11, 0 },
	{ 0, 0x1A, 0 },
	{ 0, 0x1C, 0 },
	{ 0, 0x1D, 0 },
	{ 0, 0, 0x2A000001 }
};

static const cfg_op_t _di_init2[113] = {
	{ 0, DC_CMD_STATE_ACCESS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_DV_CONTROL, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_CSC_YOF,   0xF0 },
	{ 0, DC_WIN_CSC_KYRGB, 0x12A },
	{ 0, DC_WIN_CSC_KUR,   0 },
	{ 0, DC_WIN_CSC_KVR,   0x198 },
	{ 0, DC_WIN_CSC_KUG,   0x39B },
	{ 0, DC_WIN_CSC_KVG,   0x32F },
	{ 0, DC_WIN_CSC_KUB,   0x204 },
	{ 0, DC_WIN_CSC_KVB,   0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_DV_CONTROL, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_CSC_YOF,   0xF0 },
	{ 0, DC_WIN_CSC_KYRGB, 0x12A },
	{ 0, DC_WIN_CSC_KUR,   0 },
	{ 0, DC_WIN_CSC_KVR,   0x198 },
	{ 0, DC_WIN_CSC_KUG,   0x39B },
	{ 0, DC_WIN_CSC_KVG,   0x32F },
	{ 0, DC_WIN_CSC_KUB,   0x204 },
	{ 0, DC_WIN_CSC_KVB,   0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_DV_CONTROL, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_CSC_YOF,   0xF0 },
	{ 0, DC_WIN_CSC_KYRGB, 0x12A },
	{ 0, DC_WIN_CSC_KUR,   0 },
	{ 0, DC_WIN_CSC_KVR,   0x198 },
	{ 0, DC_WIN_CSC_KUG,   0x39B },
	{ 0, DC_WIN_CSC_KVG,   0x32F },
	{ 0, DC_WIN_CSC_KUB,   0x204 },
	{ 0, DC_WIN_CSC_KVB,   0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_COLOR_CONTROL, BASE_COLOR_SIZE_888 },
	{ 0, DC_DISP_DISP_INTERFACE_CONTROL, DISP_DATA_FORMAT_DF1P1C },
	{ 0, DC_COM_PIN_OUTPUT_POLARITY(1), 0x1000000 },
	{ 0, DC_COM_PIN_OUTPUT_POLARITY(3), 0 },
	{ 0, DC_DISP_BLEND_BACKGROUND_COLOR, 0 },
	{ 0, DC_COM_CRC_CONTROL, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE | WIN_A_UPDATE | WIN_B_UPDATE | WIN_C_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ | WIN_A_ACT_REQ | WIN_B_ACT_REQ | WIN_C_ACT_REQ },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, 0x716, 0x10000FF },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, 0x716, 0x10000FF },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, 0x716, 0x10000FF },
	{ 0, DC_CMD_DISPLAY_COMMAND_OPTION0, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_COMMAND, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE | WIN_A_UPDATE | WIN_B_UPDATE | WIN_C_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ | WIN_A_ACT_REQ | WIN_B_ACT_REQ | WIN_C_ACT_REQ },
	{ 0, DC_CMD_STATE_ACCESS, 0 },
	{ 0, DC_DISP_DISP_TIMING_OPTIONS, 0 },
	{ 0, DC_DISP_REF_TO_SYNC, (1 << 16) },
	{ 0, DC_DISP_SYNC_WIDTH,  0x10048 },
	{ 0, DC_DISP_BACK_PORCH,  0x90048 },
	{ 0, DC_DISP_ACTIVE,      0x50002D0 },
	{ 0, DC_DISP_FRONT_PORCH, 0xA0088 },
	{ 0, DC_DISP_SHIFT_CLOCK_OPTIONS, SC1_H_QUALIFIER_NONE | SC0_H_QUALIFIER_NONE },
	{ 0, DC_COM_PIN_OUTPUT_ENABLE(1), 0 },
	{ 0, DC_DISP_DATA_ENABLE_OPTIONS, DE_SELECT_ACTIVE | DE_CONTROL_NORMAL },
	{ 0, DC_DISP_DISP_INTERFACE_CONTROL, DISP_DATA_FORMAT_DF1P1C },
	{ 0, DC_DISP_DISP_CLOCK_CONTROL, 0 },
	{ 0, DC_CMD_DISPLAY_COMMAND_OPTION0, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_COMMAND, DISP_CTRL_MODE_C_DISPLAY },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_STATE_ACCESS, READ_MUX | WRITE_MUX },
	{ 0, DC_DISP_FRONT_PORCH, 0xA0088 },
	{ 0, DC_CMD_STATE_ACCESS, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_GENERAL_INCR_SYNCPT, 0x301 },
	{ 0, DC_CMD_GENERAL_INCR_SYNCPT, 0x301 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_STATE_ACCESS, 0 },
	{ 0, DC_DISP_DISP_CLOCK_CONTROL, PIXEL_CLK_DIVIDER_PCD1 | SHIFT_CLK_DIVIDER(4) },
	{ 0, DC_DISP_DISP_COLOR_CONTROL, BASE_COLOR_SIZE_888 },
	{ 0, DC_CMD_DISPLAY_COMMAND_OPTION0, 0 }
};

static const cfg_op_t _di_deinit[17] = {
	{ 0, DC_DISP_FRONT_PORCH, 0xA0088 },
	{ 0, DC_CMD_INT_MASK, 0 },
	{ 0, DC_CMD_STATE_ACCESS, 0 },
	{ 0, DC_CMD_INT_ENABLE, 0 },
	{ 0, DC_CMD_CONT_SYNCPT_VSYNC, 0 },
	{ 0, DC_CMD_DISPLAY_COMMAND, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_GENERAL_INCR_SYNCPT, 0x301 },
	{ 0, DC_CMD_GENERAL_INCR_SYNCPT, 0x301 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
	{ 0, DC_CMD_DISPLAY_POWER_CONTROL, 0 },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE },
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ },
};

static const cfg_op_t _dsi_deinit_erista[16] = {
	{ 0, DSI_POWER_CONTROL, 0 },
	{ 0, DSI_PAD_CONTROL_1, 0 },
	{ 0, DSI_PHY_TIMING_0, 0x6070601 },
	{ 0, DSI_PHY_TIMING_1, 0x40A0E05 },
	{ 0, DSI_PHY_TIMING_2, 0x30109 },
	{ 0, DSI_BTA_TIMING, 0x190A14 },
	{ 0, DSI_TIMEOUT_0, DSI_TIMEOUT_LRX(0x2000) | DSI_TIMEOUT_HTX(0xFFFF)  },
	{ 0, DSI_TIMEOUT_1, DSI_TIMEOUT_PR(0x765) | DSI_TIMEOUT_TA(0x2000) },
	{ 0, DSI_TO_TALLY, 0 },
	{ 0, DSI_HOST_CONTROL, DSI_HOST_CONTROL_CRC_RESET | DSI_HOST_CONTROL_TX_TRIG_HOST | DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC },
	{ 0, DSI_CONTROL, DSI_CONTROL_LANES(3) | DSI_CONTROL_HOST_ENABLE },
	{ 0, DSI_POWER_CONTROL, DSI_POWER_CONTROL_ENABLE },
	{ 0, DSI_MAX_THRESHOLD, 0x40 },
	{ 0, DSI_TRIGGER, 0 },
	{ 0, DSI_TX_CRC, 0 },
	{ 0, DSI_INIT_SEQ_CONTROL, 0 }
};

static const cfg_op_t _dsi_deinit_mariko[16] = {
	{ 0, DSI_POWER_CONTROL, 0 },
	{ 0, DSI_PAD_CONTROL_1, 0 },
	{ 0, DSI_PHY_TIMING_0, 0x6070603 },
	{ 0, DSI_PHY_TIMING_1, 0x40A0E05 },
	{ 0, DSI_PHY_TIMING_2, 0x30109 },
	{ 0, DSI_BTA_TIMING, 0x190A14 },
	{ 0, DSI_TIMEOUT_0, DSI_TIMEOUT_LRX(0x2000) | DSI_TIMEOUT_HTX(0xFFFF)  },
	{ 0, DSI_TIMEOUT_1, DSI_TIMEOUT_PR(0x765) | DSI_TIMEOUT_TA(0x2000) },
	{ 0, DSI_TO_TALLY, 0 },
	{ 0, DSI_HOST_CONTROL, DSI_HOST_CONTROL_CRC_RESET | DSI_HOST_CONTROL_TX_TRIG_HOST | DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC },
	{ 0, DSI_CONTROL, DSI_CONTROL_LANES(3) | DSI_CONTROL_HOST_ENABLE },
	{ 0, DSI_POWER_CONTROL, DSI_POWER_CONTROL_ENABLE },
	{ 0, DSI_MAX_THRESHOLD, 0x40 },
	{ 0, DSI_TRIGGER, 0 },
	{ 0, DSI_TX_CRC, 0 },
	{ 0, DSI_INIT_SEQ_CONTROL, 0 }
};

static const cfg_op_t _dsi_jdi_deinit[22] = {
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0x9483FFB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x2139 },
	{ 0, DSI_WR_DATA, 0x191919D5 },
	{ 0, DSI_WR_DATA, 0x19191919 },
	{ 0, DSI_WR_DATA, 0x19191919 },
	{ 0, DSI_WR_DATA, 0x19191919 },
	{ 0, DSI_WR_DATA, 0x19191919 },
	{ 0, DSI_WR_DATA, 0x19191919 },
	{ 0, DSI_WR_DATA, 0x19191919 },
	{ 0, DSI_WR_DATA, 0x19191919 },
	{ 0, DSI_WR_DATA, 0x19 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0xB39 },
	{ 0, DSI_WR_DATA, 0x4F0F41B1 },
	{ 0, DSI_WR_DATA, 0xF179A433 },
	{ 0, DSI_WR_DATA, 0x2D81 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0xB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST }
};

static const cfg_op_t _dsi_auo_v1_deinit[38] = {
    { 0, DSI_WR_DATA, 0x439 },
    { 0, DSI_WR_DATA, 0x9483FFB9 },
    { 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
    { 0, DSI_WR_DATA, 0x2C39 },
    { 0, DSI_WR_DATA, 0x191919D5 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
    { 0, DSI_WR_DATA, 0x2C39 },
    { 0, DSI_WR_DATA, 0x191919D6 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_WR_DATA, 0x19191919 },
    { 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
    { 0, DSI_WR_DATA, 0xB39 },
    { 0, DSI_WR_DATA, 0x711148B1 },
    { 0, DSI_WR_DATA, 0x71143209 },
    { 0, DSI_WR_DATA, 0x114D31 },
    { 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
    { 0, DSI_WR_DATA, 0x439 },
    { 0, DSI_WR_DATA, 0xB9 },
    { 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
    { 1, 5, 0 },
};

static const cfg_op_t _dsi_innolux_v2_deinit[10] = {
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0x9483FFB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
	{ 0, DSI_WR_DATA, 0xB39 },
	{ 0, DSI_WR_DATA, 0x751548B1 },
	{ 0, DSI_WR_DATA, 0x71143209 },
	{ 0, DSI_WR_DATA, 0x115631 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
};

static const cfg_op_t _dsi_auo_v2_deinit[10] = {
	{ 0, DSI_WR_DATA, 0x439 },
	{ 0, DSI_WR_DATA, 0x9483FFB9 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
	{ 0, DSI_WR_DATA, 0xB39 },
	{ 0, DSI_WR_DATA, 0x711148B1 },
	{ 0, DSI_WR_DATA, 0x71143209 },
	{ 0, DSI_WR_DATA, 0x114D31 },
	{ 0, DSI_TRIGGER, DSI_TRIGGER_HOST },
	{ 1, 5, 0 },
};

static const cfg_op_t _di_one_color[8] = {
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, DSI_ENABLE },
	{ 0, DC_CMD_DISPLAY_COMMAND, DISP_CTRL_MODE_C_DISPLAY }
};

static const cfg_op_t _di_framebuffer[32] = {
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_C_SELECT }, //Enable window C.
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_B_SELECT }, //Enable window B.
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_CMD_DISPLAY_WINDOW_HEADER, WINDOW_A_SELECT }, //Enable window A.
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, DSI_ENABLE }, //DSI_ENABLE
	{ 0, DC_WIN_COLOR_DEPTH, WIN_COLOR_DEPTH_B8G8R8A8 }, //T_A8R8G8B8 //NX Default: T_A8B8G8R8, WIN_COLOR_DEPTH_R8G8B8A8
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_WIN_POSITION, 0 }, //(0,0)
	{ 0, DC_WIN_H_INITIAL_DDA, 0 },
	{ 0, DC_WIN_V_INITIAL_DDA, 0 },
	{ 0, DC_WIN_PRESCALED_SIZE, V_PRESCALED_SIZE(1280) | H_PRESCALED_SIZE(2880) }, //Pre-scaled size: 1280x2880 bytes.
	{ 0, DC_WIN_DDA_INC, V_DDA_INC(0x1000) | H_DDA_INC(0x1000) },
	{ 0, DC_WIN_SIZE, V_SIZE(1280) | H_SIZE(720) }, //Window size: 1280 vertical lines x 720 horizontal pixels.
	{ 0, DC_WIN_LINE_STRIDE, 0x6000C00 }, //768*2x768*4 (= 0x600 x 0xC00) bytes, see TRM for alignment requirements.
	{ 0, DC_WIN_BUFFER_CONTROL, 0 },
	{ 0, DC_WINBUF_SURFACE_KIND, 0 }, //Regular surface.
	{ 0, DC_WINBUF_START_ADDR, 0xC0000000 }, //Framebuffer address.
	{ 0, DC_WINBUF_ADDR_H_OFFSET, 0 },
	{ 0, DC_WINBUF_ADDR_V_OFFSET, 0 },
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, DSI_ENABLE }, //DSI_ENABLE
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, DSI_ENABLE }, //DSI_ENABLE
	{ 0, DC_WIN_WIN_OPTIONS, 0 },
	{ 0, DC_DISP_DISP_WIN_OPTIONS, DSI_ENABLE }, //DSI_ENABLE
	{ 0, DC_WIN_WIN_OPTIONS, WIN_ENABLE }, //Enable window AD.
	{ 0, DC_CMD_DISPLAY_COMMAND, DISP_CTRL_MODE_C_DISPLAY }, //DISPLAY_CTRL_MODE: continuous display.
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_UPDATE | WIN_A_UPDATE }, //General update; window A update.
	{ 0, DC_CMD_STATE_CONTROL, GENERAL_ACT_REQ | WIN_A_ACT_REQ } //General activation request; window A activation request.
};
