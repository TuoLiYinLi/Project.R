#pragma once

enum class AnimationType
{
	//debug
	//
	debug_banned,
	//
	debug_physics_outside,
	debug_physics_air,
	debug_physics_support,
	debug_physics_liquid,
	debug_physics_solid,
	debug_physics_chara,
	debug_physics_projectile,
	//
	debug_sequence_white,
	debug_sequence_red,
	debug_sequence_yellow,
	debug_sequence_green,
	debug_sequence_blue,
	debug_sequence_black,

	//UI
	ui_button_exit_default,
	ui_button_exit_highlight,
	ui_button_exit_pressed,

	ui_inspector_panel,

	ui_button_menu_default,
	ui_button_menu_highlight,
	ui_button_menu_pressed,
	ui_button_grid_banned,

	ui_button_grid_default,
	ui_button_grid_highlight,
	ui_button_grid_pressed,

	ui_button_controller_mask,

	ui_energy_bar,
	//monster
	monster_slime_idle,
	monster_slime_moving,
	monster_slime_dead,
	monster_slime_absorb,
	monster_slime_eject,
	//warrior
	warrior_miner_pickaxe_idle,
	warrior_miner_pickaxe_moving,
	warrior_miner_pickaxe_dead,
	warrior_miner_pickaxe_dig,

	//facility
	facility_dirt_background_1,
	facility_dirt_background_2,
	facility_dirt_background_3,
	facility_dirt_background_4,
	facility_dirt_background_5,
	facility_dirt_background_6,
	facility_dirt_background_7,
	facility_dirt_background_8,

	facility_dirt_solid_1,
	facility_dirt_solid_2,
	facility_dirt_solid_3,

	facility_soil_cracked_1,
	facility_soil_cracked_2,
	facility_soil_cracked_3,
	facility_soil_cracked_4,

	facility_water_clean,
	facility_water_clean_top,
	facility_water_blood,
	facility_water_blood_top,
	facility_water_swamp,
	facility_water_swamp_top,

	facility_ladder_wooden_1,
	facility_ladder_wooden_2,
	facility_ladder_wooden_3,
	facility_ladder_wooden_4,
	facility_ladder_wooden_5,
	facility_ladder_wooden_6,

	//projectile
	projectile_chop,
	projectile_little_magic_ball,
	projectile_little_slime_ball,
	//particle
	particle_goldust,
	size,//末尾，代表了总数量
};
