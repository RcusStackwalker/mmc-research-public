
void __attribute__((weak)) update_current_gear();
void __attribute__((weak)) update_nlts_target_torque_limit();
void __attribute__((weak)) update_revolution_limit();
void __attribute__((weak)) update_load1byte();
void __attribute__((weak)) update_shift_light();
void __attribute__((weak)) update_cvt_dash_data();

void update_current_gear()
{

}

void update_nlts_target_torque_limit()
{

}

void update_revolution_limit()
{

}

void update_load1byte()
{

}

void update_shift_light()
{

}

void update_cvt_dash_data()
{

}

void new_update_gpio_outputs()
{
	update_gpio_outputs();
	update_current_gear();
	update_nlts_target_torque_limit();
	update_revolution_limit();
	update_load1byte();
	update_shift_light();
	update_cvt_dash_data();
}
