#include "Arduino.h"
#include "ctrl_wheel_tract.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "srv_ui_bt/srv_ui_bt.h"
#include "ed_l298/ed_l298.h"
#include "dd_dc_motor/dd_dc_motor.h"
#include "ed_encoder/ed_encoder.h"

uint8_t ctrl_wheel_tract_target_mode = CTRL_WHEEL_TRACT_TARGET_MODE_CAN;
uint8_t ctrl_wheel_tract_fb_mode = CTRL_WHEEL_TRACT_FB_MODE_ENCODER;
uint8_t ctrl_wheel_tract_op_mode = CTRL_WHEEL_TRACT_OP_MODE;
int16_t ctrl_wheel_tract_target_step = 0;
int16_t ctrl_wheel_tract_current_step = 0;

int16_t ctrl_wheel_tract_power = 0;
int8_t ctrl_wheel_tract_enable_state = 0;

int16_t ctrl_wheel_tract_get_power()
{
    return ctrl_wheel_tract_power;
}
int16_t ctrl_wheel_tract_set_power(int16_t power)
{
    if (power > DD_DC_MOTOR_MAX_POWER)
    {
        power = DD_DC_MOTOR_MAX_POWER;
    }
    else if (power < DD_DC_MOTOR_MIN_POWER)
    {
        power = DD_DC_MOTOR_MIN_POWER;
    }
    ctrl_wheel_tract_power = power;
    return ctrl_wheel_tract_power;
}

int16_t ctrl_wheel_tract_power_up(int16_t power)
{
    power = ctrl_wheel_tract_get_power() + power;
    power = ctrl_wheel_tract_set_power(power);
    return power;
}

int16_t ctrl_wheel_tract_power_down(int16_t power)
{
    power = ctrl_wheel_tract_get_power() - power;
    power = ctrl_wheel_tract_set_power(power);
    return power;
}

int16_t ctrl_wheel_tract_get_target_step()
{
    return ctrl_wheel_tract_target_step;
}

int16_t ctrl_wheel_tract_set_target_step(int16_t step)
{

    ctrl_wheel_tract_target_step = step;
    return ctrl_wheel_tract_target_step;
}
int16_t ctrl_wheel_tract_get_current_step()
{
    return ctrl_wheel_tract_current_step;
}
int16_t ctrl_wheel_tract_set_current_step(int16_t step)
{

    ctrl_wheel_tract_current_step = step;
    return ctrl_wheel_tract_current_step;
}

int16_t ctrl_wheel_tract_step_up(int16_t step)
{
    step = ctrl_wheel_tract_get_target_step() + step;
    step = ctrl_wheel_tract_set_target_step(step);
    return step;
}
int16_t ctrl_wheel_tract_step_down(int16_t step)
{
    step = ctrl_wheel_tract_get_target_step() - step;
    step = ctrl_wheel_tract_set_target_step(step);
    return step;
}

int8_t ctrl_wheel_tract_enable()
{
    ctrl_wheel_tract_enable_state = 1;
    return ctrl_wheel_tract_enable_state;
}
int8_t ctrl_wheel_tract_disable()
{
    ctrl_wheel_tract_enable_state = 0;
    return ctrl_wheel_tract_enable_state;
}
int8_t ctrl_wheel_tract_is_enabled()
{
    return ctrl_wheel_tract_enable_state;
}

uint8_t ctrl_wheel_tract_set_mode(uint8_t mode)
{
    ctrl_wheel_tract_enable_state = mode;
    return ctrl_wheel_tract_enable_state;
}

uint8_t ctrl_wheel_tract_set_target_mode(uint8_t mode)
{
    ctrl_wheel_tract_target_mode = mode;
    return ctrl_wheel_tract_target_mode;
}
uint8_t ctrl_wheel_tract_get_target_mode()
{
    return ctrl_wheel_tract_target_mode;
}
uint8_t ctrl_wheel_tract_set_fb_mode(uint8_t mode)
{
    ctrl_wheel_tract_fb_mode = mode;
    return ctrl_wheel_tract_fb_mode;
}
uint8_t ctrl_wheel_tract_get_fb_mode()
{
    return ctrl_wheel_tract_fb_mode;
}
uint8_t ctrl_wheel_tract_set_op_mode(uint8_t mode)
{
    ctrl_wheel_tract_op_mode = mode;
    return ctrl_wheel_tract_op_mode;
}
uint8_t ctrl_wheel_tract_get_op_mode()
{
    return ctrl_wheel_tract_op_mode;
}
uint8_t ctrl_wheel_tract_is_step_mode()
{
    return ctrl_wheel_tract_op_mode == CTRL_WHEEL_TRACT_OP_MODE_STEP;
}
void ctrl_wheel_tract_setup()
{
    ctrl_wheel_tract_set_target_step(0);
    ctrl_wheel_tract_set_current_step(0);

    ctrl_wheel_tract_set_mode(CTRL_WHEEL_TRACT_MODE);
    ctrl_wheel_tract_set_target_mode(CTRL_WHEEL_TRACT_TARGET_MODE);
    ctrl_wheel_tract_set_fb_mode(CTRL_WHEEL_TRACT_FB_MODE);
    ctrl_wheel_tract_set_op_mode(CTRL_WHEEL_TRACT_OP_MODE);
    ctrl_wheel_tract_set_power(0);
}

void ctrl_wheel_tract_loop()
{
    int16_t traction_power;

    int16_t target_step;
    int16_t current_step;

    if (ctrl_wheel_tract_is_enabled())
    {
        if (ctrl_wheel_tract_fb_mode == CTRL_WHEEL_TRACT_FB_MODE_ENCODER)
        {
            current_step = ed_encoder_get_counter();
            ctrl_wheel_tract_current_step = current_step;
        }
        // else if(ctrl_wheel_tract_fb_mode == CTRL_WHEEL_TRACT_FB_MODE_POTENTIOMETER)
        // {
        //     current_step = dd_can_signal_get_potentiometer_traction() * 2;
        //     ctrl_wheel_tract_current_step = current_step;
        // }
        else if (ctrl_wheel_tract_fb_mode == CTRL_WHEEL_TRACT_FB_MODE_TIMER)
        {
            if (ctrl_wheel_tract_current_step > ctrl_wheel_tract_target_step)
            {
                ctrl_wheel_tract_current_step--;
            }
            else if (ctrl_wheel_tract_current_step < ctrl_wheel_tract_target_step)
            {
                ctrl_wheel_tract_current_step++;
            }
            else
            {
                ctrl_wheel_tract_current_step = ctrl_wheel_tract_target_step;
            }
        }

        current_step = ctrl_wheel_tract_current_step;
        ctrl_wheel_tract_set_current_step(current_step);

        if (ctrl_wheel_tract_target_mode == CTRL_WHEEL_TRACT_TARGET_MODE_CAN)
        {
            if (ctrl_wheel_tract_op_mode == CTRL_WHEEL_TRACT_OP_MODE_STEP)
            {
                target_step = dd_can_signal_get_bt_ui_steering() * 2;
                ctrl_wheel_tract_set_target_step(traction_power);
            }
            else{
                traction_power = dd_can_signal_get_bt_ui_power() * 2;
            }
        }
        else if (ctrl_wheel_tract_target_mode == CTRL_WHEEL_TRACT_TARGET_MODE_BT)
        {
            traction_power = srv_ui_bt_get_power()*2;
            ctrl_wheel_tract_set_power(traction_power);
        }

        else if (ctrl_wheel_tract_target_mode == CTRL_WHEEL_TRACT_TARGET_MODE_MANUAL)
        {
            traction_power = ctrl_wheel_tract_get_power();
        }

        ctrl_wheel_tract_set_target_step(target_step);
        ctrl_wheel_tract_set_power(traction_power);

        if (ctrl_wheel_tract_op_mode == CTRL_WHEEL_TRACT_OP_MODE_STEP)
        {   
            traction_power = ctrl_wheel_tract_set_power(255);

            if (target_step > current_step)
            {
                dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, ctrl_wheel_tract_power);
            }
            else if (target_step < current_step)
            {
                dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, -ctrl_wheel_tract_power);
            }
            else
            {
                dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, 0);
            }
        }
        else if (ctrl_wheel_tract_op_mode == CTRL_WHEEL_TRACT_OP_MODE_CONTINUOUS)
        {
            traction_power = ctrl_wheel_tract_get_power();
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, traction_power);
        }
        else if (ctrl_wheel_tract_op_mode == CTRL_WHEEL_TRACT_OP_MODE_POWER)
        {
            traction_power = ctrl_wheel_tract_get_power();
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, traction_power);
        }
        //     traction_power = ctrl_wheel_tract_get_power();

        // dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, traction_power);
    }
    else
    {
        traction_power = ctrl_wheel_tract_get_power();
        dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, 0);
    }
}