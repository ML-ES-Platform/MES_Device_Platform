#include "Arduino.h"
#include "ctrl_wheel_steer.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "srv_ui_bt/srv_ui_bt.h"
#include "dd_dc_motor/dd_dc_motor.h"
#include "ed_encoder/ed_encoder.h"
#include "ed_l298/ed_l298.h"

#define CTRL_WHEEL_STEER_ANGLE_MAX (10000)
#define CTRL_WHEEL_STEER_ANGLE_MIN (-10000)

uint8_t ctrl_wheel_steer_target_mode = CTRL_WHEEL_STEER_TARGET_MODE;
uint8_t ctrl_wheel_steer_fb_mode = CTRL_WHEEL_STEER_FB_MODE;
uint8_t ctrl_wheel_steer_op_mode = CTRL_WHEEL_STEER_OP_MODE;
int16_t ctrl_wheel_steer_target_angle = 0;
int16_t ctrl_wheel_steer_current_angle = 0;
int16_t ctrl_wheel_steer_power = 0;
int8_t ctrl_wheel_steer_enable_state = CTRL_WHEEL_STEER_MODE;

int16_t ctrl_wheel_steer_get_power()
{
    return ctrl_wheel_steer_power;
}
int16_t ctrl_wheel_steer_set_power(int16_t power)
{
    if (power > DD_DC_MOTOR_MAX_POWER)
    {
        power = DD_DC_MOTOR_MAX_POWER;
    }
    else if (power < 0)
    {
        power = 0;
    }
    ctrl_wheel_steer_power = power;
    return ctrl_wheel_steer_power;
}

int16_t ctrl_wheel_steer_power_up(int16_t power)
{
    power = ctrl_wheel_steer_get_power() + power;
    power = ctrl_wheel_steer_set_power(power);
    return power;
}

int16_t ctrl_wheel_steer_power_down(int16_t power)
{
    power = ctrl_wheel_steer_get_power() - power;
    power = ctrl_wheel_steer_set_power(power);
    return power;
}

int16_t ctrl_wheel_steer_get_target_angle()
{
    return ctrl_wheel_steer_target_angle;
}

int16_t ctrl_wheel_steer_set_target_angle(int16_t angle)
{
    if (angle > CTRL_WHEEL_STEER_ANGLE_MAX)
    {
        angle = CTRL_WHEEL_STEER_ANGLE_MAX;
    }
    else if (angle < CTRL_WHEEL_STEER_ANGLE_MIN)
    {
        angle = CTRL_WHEEL_STEER_ANGLE_MIN;
    }
    ctrl_wheel_steer_target_angle = angle;
    return ctrl_wheel_steer_target_angle;
}
int16_t ctrl_wheel_steer_get_current_angle()
{
    return ctrl_wheel_steer_current_angle;
}
int16_t ctrl_wheel_steer_set_current_angle(int16_t angle)
{
    if (angle > CTRL_WHEEL_STEER_ANGLE_MAX)
    {
        angle = CTRL_WHEEL_STEER_ANGLE_MAX;
    }
    else if (angle < CTRL_WHEEL_STEER_ANGLE_MIN)
    {
        angle = CTRL_WHEEL_STEER_ANGLE_MIN;
    }
    ctrl_wheel_steer_current_angle = angle;
    return ctrl_wheel_steer_current_angle;
}

int16_t ctrl_wheel_steer_turn_right(int16_t angle)
{
    angle = ctrl_wheel_steer_get_target_angle() + angle;
    angle = ctrl_wheel_steer_set_target_angle(angle);
    return angle;
}
int16_t ctrl_wheel_steer_turn_left(int16_t angle)
{
    angle = ctrl_wheel_steer_get_target_angle() - angle;
    angle = ctrl_wheel_steer_set_target_angle(angle);
    return angle;
}

int8_t ctrl_wheel_steer_enable()
{
    ctrl_wheel_steer_enable_state = 1;
    return ctrl_wheel_steer_enable_state;
}
int8_t ctrl_wheel_steer_disable()
{
    ctrl_wheel_steer_enable_state = 0;
    return ctrl_wheel_steer_enable_state;
}
int8_t ctrl_wheel_steer_is_enabled()
{
    return ctrl_wheel_steer_enable_state;
}

uint8_t ctrl_wheel_steer_set_mode(uint8_t mode)
{
    ctrl_wheel_steer_enable_state = mode;
    return ctrl_wheel_steer_enable_state;
}

uint8_t ctrl_wheel_steer_set_target_mode(uint8_t mode)
{
    ctrl_wheel_steer_target_mode = mode;
    return ctrl_wheel_steer_target_mode;
}
uint8_t ctrl_wheel_steer_get_target_mode()
{
    return ctrl_wheel_steer_target_mode;
}
uint8_t ctrl_wheel_steer_set_fb_mode(uint8_t mode)
{
    ctrl_wheel_steer_fb_mode = mode;
    return ctrl_wheel_steer_fb_mode;
}
uint8_t ctrl_wheel_steer_get_fb_mode()
{
    return ctrl_wheel_steer_fb_mode;
}

void ctrl_wheel_steer_setup()
{
    ctrl_wheel_steer_set_target_angle(0);
    ctrl_wheel_steer_set_current_angle(0);

    ctrl_wheel_steer_set_mode(CTRL_WHEEL_STEER_MODE);
    ctrl_wheel_steer_set_target_mode(CTRL_WHEEL_STEER_TARGET_MODE);
    ctrl_wheel_steer_set_fb_mode(CTRL_WHEEL_STEER_FB_MODE);
    ctrl_wheel_steer_set_power(CTRL_WHEEL_STEER_POWER);
}

void ctrl_wheel_steer_loop()
{
    int16_t target_angle;
    int16_t current_angle;

    // int16_t steering_power;
    // steering_power = ctrl_wheel_steer_get_power();


    if (ctrl_wheel_steer_is_enabled())
    {
        if (ctrl_wheel_steer_fb_mode == CTRL_WHEEL_STEER_FB_MODE_ENCODER)
        {
            current_angle = ed_encoder_get_counter();
            ctrl_wheel_steer_current_angle = current_angle;
        }
        // else if(ctrl_wheel_steer_fb_mode == CTRL_WHEEL_STEER_FB_MODE_POTENTIOMETER)
        // {
        //     current_angle = dd_can_signal_get_potentiometer_steering() * 2;
        //     ctrl_wheel_steer_current_angle = current_angle;
        // }
        else if (ctrl_wheel_steer_fb_mode == CTRL_WHEEL_STEER_FB_MODE_TIMER)
        {
            if (ctrl_wheel_steer_current_angle > ctrl_wheel_steer_target_angle)
            {
                ctrl_wheel_steer_current_angle--;
            }
            else if (ctrl_wheel_steer_current_angle < ctrl_wheel_steer_target_angle)
            {
                ctrl_wheel_steer_current_angle++;
            }
            else
            {
                ctrl_wheel_steer_current_angle = ctrl_wheel_steer_target_angle;
            }
        }

        current_angle = ctrl_wheel_steer_current_angle;
        ctrl_wheel_steer_set_current_angle(current_angle);

        if (ctrl_wheel_steer_target_mode == CTRL_WHEEL_STEER_TARGET_MODE_CAN)
        {
            target_angle = dd_can_signal_get_bt_ui_steering();
            ctrl_wheel_steer_set_target_angle(target_angle);
        }
        else if (ctrl_wheel_steer_target_mode == CTRL_WHEEL_STEER_TARGET_MODE_BT)
        {
            target_angle = srv_ui_bt_get_steering();
            ctrl_wheel_steer_set_target_angle(target_angle);
        }
        else if (ctrl_wheel_steer_target_mode == CTRL_WHEEL_STEER_TARGET_MODE_MANUAL)
        {
            target_angle = ctrl_wheel_steer_get_target_angle();
        }

        ctrl_wheel_steer_set_target_angle(target_angle);

        if (target_angle > current_angle)
        {
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, ctrl_wheel_steer_power);
        }
        else if (target_angle < current_angle)
        {
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, -ctrl_wheel_steer_power);
        }
        else
        {
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, 0);
        }
    }
    else
    {
        dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, 0);// check this
    }

}