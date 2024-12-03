#include "Dancing.hpp"

void Dancing::init(const uint8_t *pin)
{
    for (int i = 0; i < 6; i++)
    {
        _pin[i] = pin[i];
        _servo[i].attach(_pin[i], _ch[i], _wr_min, _wr_max);
        _servo[i].write(_pin[i], 90);
    }
}

void Dancing::setDeg(uint8_t pose, int *deg)
{
    _deg_r[pose] = deg[0];
    _deg_l[pose] = deg[1];
}

void Dancing::setPose(uint8_t *pose)
{
    for (int i; i < 3; i++)
    {
        _servo[i * 2].write(_pin[i * 2], _deg_r[pose[i]]);
        _servo[i * 2 + 1].write(_pin[i * 2 + 1], _deg_l[pose[i]]);
    }
}

void Dancing::setMove(uint8_t *pose1, uint8_t *pose2, unsigned long time, uint8_t div)
{
    unsigned long delta_time = time / div;
    float delta_deg_r[3], delta_deg_l[3];
    for (int i = 0; i < 3; i++)
    {
        delta_deg_r[i] = static_cast<float>(_deg_r[pose2[i]] - _deg_r[pose1[i]]) / div;
        delta_deg_l[i] = static_cast<float>(_deg_l[pose2[i]] - _deg_l[pose1[i]]) / div;
    }

    for (int i = 0; i < div; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _servo[j * 2].write(_pin[j * 2], _deg_r[pose1[j]] + delta_deg_r[j] * (i + 1));
            _servo[j * 2 + 1].write(_pin[j * 2 + 1], _deg_l[pose1[j]] + delta_deg_l[j] * (i + 1));
        }
        delay(delta_time);
    }
}

int Dancing::updateDance(unsigned long time, int last_beats, CRGB *led, uint8_t num)
{
    int beats = time / 924;
    uint8_t pose1[3], pose2[3];

    if (beats > last_beats)
    {
        switch (beats)
        {
        case 0:
        case 1:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            for (int i = 0; i < num; i++)
                led[i] = CRGB::Black;
            _led_normal = false;
            break;
        case 2:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            pose2[0] = pose2[1] = pose2[2] = STRECH;
            setPose(pose2);
            _led_normal = true;
            break;
        case 3:
        case 5:
        case 7:
        case 9:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            _led_normal = true;
            break;
        case 4:
        case 6:
        case 8:
        case 10:
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            setPose(pose1);
            _led_normal = true;
            break;
        case 11:
        case 13:
        case 15:
        case 17:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            _led_normal = true;
            break;
        case 12:
        case 16:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            setPose(pose1);
            _led_normal = true;
            break;
        case 14:
        case 18:
            pose1[0] = pose1[1] = pose1[2] = LEAN_L;
            setPose(pose1);
            _led_normal = true;
            break;
        case 19:
        case 21:
        case 23:
        case 25:
            pose1[0] = pose1[2] = SQUAT;
            pose1[1] = STRECH;
            setPose(pose1);
            _led_normal = true;
            break;
        case 20:
        case 22:
        case 24:
        case 26:
            pose1[0] = pose1[2] = STRECH;
            pose1[1] = SQUAT;
            setPose(pose1);
            _led_normal = true;
            break;
        case 27:
        case 29:
        case 31:
        case 33:
            pose1[0] = pose1[1] = pose1[2] = STAND;
            setPose(pose1);
            _led_normal = true;
            break;
        case 28:
        case 32:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            setPose(pose1);
            _led_normal = true;
            break;
        case 30:
        case 34:
            pose1[0] = pose1[1] = pose1[2] = LEAN_L;
            setPose(pose1);
            _led_normal = true;
            break;
        case 35:
            pose1[0] = pose1[1] = SQUAT;
            pose1[2] = STRECH;
            setPose(pose1);

            for (int i = 0; i < 10; i++)
            {
                led[i + 22] = CRGB::Blue;
                led[i + 32] = CRGB::Blue;
                led[i + 11] = CRGB::Black;
                led[i + 43] = CRGB::Black;
                led[i] = CRGB::Black;
                led[i + 54] = CRGB::Black;
            }
            led[10] = CRGB::Black;
            led[21] = CRGB::Black;
            led[42] = CRGB::Black;
            led[53] = CRGB::Black;
            FastLED.show();
            _led_normal = false;

            break;
        case 36:
            pose1[0] = SQUAT;
            pose1[1] = pose1[2] = STRECH;
            setPose(pose1);

            for (int i = 0; i < 10; i++)
            {
                led[i + 22] = CRGB::Blue;
                led[i + 32] = CRGB::Blue;
                led[i + 11] = CRGB::Red;
                led[i + 43] = CRGB::Red;
                led[i] = CRGB::Black;
                led[i + 54] = CRGB::Black;
            }
            led[10] = CRGB::Black;
            led[21] = CRGB::Black;
            led[42] = CRGB::Black;
            led[53] = CRGB::Black;
            FastLED.show();
            _led_normal = false;

            break;
        case 37:
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            setPose(pose1);

            for (int i = 0; i < 10; i++)
            {
                led[i + 22] = CRGB::Blue;
                led[i + 32] = CRGB::Blue;
                led[i + 11] = CRGB::Red;
                led[i + 43] = CRGB::Red;
                led[i] = CRGB::Yellow;
                led[i + 54] = CRGB::Yellow;
            }
            led[10] = CRGB::Black;
            led[21] = CRGB::Black;
            led[42] = CRGB::Black;
            led[53] = CRGB::Black;
            FastLED.show();
            _led_normal = false;

            break;
        case 38:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            _led_normal = true;
            break;
        case 39:
            pose1[0] = pose1[2] = SQUAT;
            pose1[1] = STRECH;
            setPose(pose1);

            for (int i = 0; i < 10; i++)
            {
                led[i + 22] = CRGB::Black;
                led[i + 32] = CRGB::Black;
                led[i + 11] = CRGB::Red;
                led[i + 43] = CRGB::Red;
                led[i] = CRGB::Black;
                led[i + 54] = CRGB::Black;
            }
            led[10] = CRGB::Black;
            led[21] = CRGB::Black;
            led[42] = CRGB::Black;
            led[53] = CRGB::Black;
            FastLED.show();
            _led_normal = false;

            break;
        case 40:
            pose1[1] = pose1[2] = SQUAT;
            pose1[0] = STRECH;
            setPose(pose1);

            for (int i = 0; i < 10; i++)
            {
                led[i + 22] = CRGB::Black;
                led[i + 32] = CRGB::Black;
                led[i + 11] = CRGB::Black;
                led[i + 43] = CRGB::Black;
                led[i] = CRGB::Yellow;
                led[i + 54] = CRGB::Yellow;
            }
            led[10] = CRGB::Black;
            led[21] = CRGB::Black;
            led[42] = CRGB::Black;
            led[53] = CRGB::Black;
            led[66] = CRGB::Black;
            FastLED.show();
            _led_normal = false;

            break;
        case 41:
            pose1[0] = pose1[1] = SQUAT;
            pose1[2] = STRECH;
            setPose(pose1);

            for (int i = 0; i < 10; i++)
            {
                led[i + 22] = CRGB::Blue;
                led[i + 32] = CRGB::Blue;
                led[i + 11] = CRGB::Black;
                led[i + 43] = CRGB::Black;
                led[i] = CRGB::Black;
                led[i + 54] = CRGB::Black;
            }
            led[10] = CRGB::Black;
            led[21] = CRGB::Black;
            led[42] = CRGB::Black;
            led[53] = CRGB::Black;
            FastLED.show();
            _led_normal = false;

            break;
        case 42:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            _led_normal = true;
            break;
        case 43:
            pose1[0] = pose1[1] = pose1[2] = STAND;
            setPose(pose1);
            _led_normal = true;
            break;
        case 44:
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            setPose(pose1);
            break;
        case 45:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB::Green;
            }
            FastLED.show();
            delay(460);
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            setPose(pose1);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB::Yellow;
            }
            FastLED.show();
            _led_normal = false;
            break;
        case 46:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB::Blue;
            }
            FastLED.show();
            delay(460);
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            setPose(pose1);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB::Red;
            }
            FastLED.show();
            _led_normal = false;
            break;
        case 47:
            pose1[1] = pose1[2] = STRECH;
            pose1[0] = LEAN_L;
            setPose(pose1);
            for (int j = 0; j < (num - 1) / 2 - 2; j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CRGB::Black;
                }
                for (int i = 0; i < 3; i++)
                {
                    led[31 - i - j] = CRGB::Blue;
                    led[32 + i + j] = CRGB::Blue;
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(11);
            }
            pose1[2] = STRECH;
            pose1[0] = pose1[1] = LEAN_L;
            setPose(pose1);
            for (int j = 0; j < (num - 1) / 2 - 2; j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CRGB::Black;
                }
                for (int i = 0; i < 3; i++)
                {
                    led[31 - i - j] = CRGB::Blue;
                    led[32 + i + j] = CRGB::Blue;
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(11);
            }
            _led_normal = false;
            break;
        case 48:
        case 52:
            pose1[0] = pose1[1] = pose1[2] = LEAN_L;
            setPose(pose1);
            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < (num - 1) / 2 - 2; j++)
                {
                    for (int i = 0; i < num - 1; i++)
                    {
                        led[i] = CRGB::Black;
                    }
                    for (int i = 0; i < 3; i++)
                    {
                        led[31 - i - j] = CRGB::Blue;
                        led[32 + i + j] = CRGB::Blue;
                    }
                    led[64] = CRGB(random(256), random(256), random(256));
                    FastLED.show();
                    delay(11);
                }
            }
            _led_normal = false;

            break;
        case 49:
        case 53:
            pose1[0] = pose1[1] = LEAN_L;
            pose1[2] = LEAN_R;
            setPose(pose1);
            for (int j = 0; j < (num - 1) / 2 - 2; j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CRGB::Black;
                }
                for (int i = 0; i < 3; i++)
                {
                    led[0 + i + j] = CRGB::Blue;
                    led[63 - i - j] = CRGB::Blue;
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(11);
            }
            pose1[0] = LEAN_L;
            pose1[1] = pose1[2] = LEAN_R;
            setPose(pose1);
            for (int j = 0; j < (num - 1) / 2 - 2; j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CRGB::Black;
                }
                for (int i = 0; i < 3; i++)
                {
                    led[0 + i + j] = CRGB::Blue;
                    led[63 - i - j] = CRGB::Blue;
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(11);
            }
            _led_normal = false;
            break;
        case 50:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            setPose(pose1);
            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < (num - 1) / 2 - 2; j++)
                {
                    for (int i = 0; i < num - 1; i++)
                    {
                        led[i] = CRGB::Black;
                    }
                    for (int i = 0; i < 3; i++)
                    {
                        led[0 + i + j] = CRGB::Blue;
                        led[63 - i - j] = CRGB::Blue;
                    }
                    led[64] = CRGB(random(256), random(256), random(256));
                    FastLED.show();
                    delay(11);
                }
            }
            _led_normal = false;
            break;
        case 51:
            pose1[1] = pose1[2] = LEAN_R;
            pose1[0] = LEAN_L;
            setPose(pose1);
            for (int j = 0; j < (num - 1) / 2 - 2; j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CRGB::Black;
                }
                for (int i = 0; i < 3; i++)
                {
                    led[31 - i - j] = CRGB::Blue;
                    led[32 + i + j] = CRGB::Blue;
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(11);
            }
            pose1[2] = LEAN_R;
            pose1[0] = pose1[1] = LEAN_L;
            setPose(pose1);
            for (int j = 0; j < (num - 1) / 2 - 2; j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CRGB::Black;
                }
                for (int i = 0; i < 3; i++)
                {
                    led[31 - i - j] = CRGB::Blue;
                    led[32 + i + j] = CRGB::Blue;
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(11);
            }
            _led_normal = false;
            break;
        case 54:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            setPose(pose1);
            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < (num - 1) / 2 - 2; j++)
                {
                    for (int i = 0; i < num - 1; i++)
                    {
                        led[i] = CRGB::Black;
                    }
                    for (int i = 0; i < 3; i++)
                    {
                        led[0 + i + j] = CRGB::Blue;
                        led[63 - i - j] = CRGB::Blue;
                    }
                    led[64] = CRGB(random(256), random(256), random(256));
                    FastLED.show();
                    delay(11);
                }
            }
            _led_normal = true;
            break;
        case 55:
        case 59:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            pose2[0] = pose2[1] = pose2[2] = SQUAT;
            setMove(pose1, pose2, 700, 70);
            _led_normal = true;
            _led_normal = true;
            break;
        case 56:
        case 60:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            pose2[0] = pose2[1] = pose2[2] = LEAN_L;
            setMove(pose1, pose2, 700, 70);
            _led_normal = true;
            break;
        case 57:
        case 61:
            pose1[0] = pose1[1] = pose1[2] = LEAN_L;
            pose2[0] = pose2[1] = pose2[2] = STRECH;
            setMove(pose1, pose2, 700, 70);
            _led_normal = true;
            break;
        case 58:
        case 62:
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            pose2[0] = pose2[1] = pose2[2] = LEAN_R;
            setMove(pose1, pose2, 700, 70);
            _led_normal = true;
            break;
        case 63:
        case 65:
        case 67:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            pose2[0] = pose2[1] = pose2[2] = SQUAT;
            setMove(pose1, pose2, 350, 35);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            pose2[0] = pose2[1] = pose2[2] = LEAN_L;
            setMove(pose1, pose2, 350, 35);
            _led_normal = true;
            break;
        case 64:
        case 66:
        case 68:
            pose1[0] = pose1[1] = pose1[2] = LEAN_L;
            pose2[0] = pose2[1] = pose2[2] = STRECH;
            setMove(pose1, pose2, 350, 35);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            pose2[0] = pose2[1] = pose2[2] = LEAN_R;
            setMove(pose1, pose2, 350, 35);
            _led_normal = true;
            break;
        case 69:
        case 71:
        case 73:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            pose2[0] = pose2[1] = pose2[2] = STRECH;
            setMove(pose1, pose2, 350, 35);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            pose2[0] = pose2[1] = pose2[2] = LEAN_L;
            setMove(pose1, pose2, 350, 35);
            _led_normal = true;
            break;
        case 70:
        case 72:
        case 74:
            pose1[0] = pose1[1] = pose1[2] = LEAN_L;
            pose2[0] = pose2[1] = pose2[2] = SQUAT;
            setMove(pose1, pose2, 350, 35);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            pose2[0] = pose2[1] = pose2[2] = LEAN_R;
            setMove(pose1, pose2, 350, 35);
            _led_normal = true;
            break;
        case 75:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            pose2[1] = pose2[2] = LEAN_R;
            pose2[0] = STRECH;
            setMove(pose1, pose2, 350, 35);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            pose1[0] = LEAN_L;
            pose1[1] = STRECH;
            pose1[2] = LEAN_R;
            setMove(pose2, pose1, 400, 40);
            _led_normal = true;
            break;
        case 76:
        case 78:
        case 80:
        case 82:
            pose1[0] = LEAN_L;
            pose1[1] = STRECH;
            pose1[2] = LEAN_R;
            pose2[1] = LEAN_L;
            pose2[2] = STRECH;
            pose2[0] = SQUAT;
            setMove(pose1, pose2, 350, 35);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            pose1[2] = LEAN_L;
            pose1[0] = LEAN_R;
            pose1[1] = SQUAT;
            setMove(pose2, pose1, 400, 40);
            _led_normal = true;
            break;
        case 77:
        case 79:
        case 81:
            pose1[2] = LEAN_L;
            pose1[0] = LEAN_R;
            pose1[1] = SQUAT;
            pose2[1] = LEAN_R;
            pose2[0] = STRECH;
            pose2[2] = SQUAT;
            setMove(pose1, pose2, 350, 35);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            pose1[0] = LEAN_L;
            pose1[2] = LEAN_R;
            pose1[1] = STRECH;
            setMove(pose2, pose1, 350, 35);
            _led_normal = true;
            break;
        case 83:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            _led_normal = true;
            break;
        case 84:
        case 86:
            pose1[0] = LEAN_L;
            pose1[1] = STRECH;
            pose1[2] = LEAN_R;
            setPose(pose1);

            for (int j = 0; j < 256 - 3 * (num - 1); j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CHSV(j + i * 3, 255, 255);
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(10);
            }

            _led_normal = false;
            break;
        case 85:
            pose1[0] = LEAN_R;
            pose1[1] = SQUAT;
            pose1[2] = LEAN_L;
            setPose(pose1);

            for (int j = 0; j < 256 - 3 * (num - 1); j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CHSV(j + i * 3, 255, 255);
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(10);
            }

            _led_normal = false;
            break;
        case 87:
            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);
            _led_normal = true;
            break;
        case 88:
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            setPose(pose1);
            _led_normal = true;
            break;
        case 89:
        case 91:
            pose1[0] = pose1[1] = pose1[2] = LEAN_R;
            setPose(pose1);

            for (int j = 0; j < 256 - 3 * (num - 1); j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CHSV(j + i * 3, 255, 255);
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(10);
            }

            _led_normal = false;
            break;
        case 90:
        case 92:
            pose1[0] = pose1[1] = pose1[2] = LEAN_L;
            setPose(pose1);

            for (int j = 0; j < 256 - 3 * (num - 1); j++)
            {
                for (int i = 0; i < num - 1; i++)
                {
                    led[i] = CHSV(j + i * 3, 255, 255);
                }
                led[64] = CRGB(random(256), random(256), random(256));
                FastLED.show();
                delay(10);
            }

            _led_normal = false;
            break;

        case 93:
            pose1[0] = pose1[1] = pose1[2] = STRECH;
            setPose(pose1);
            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            delay(460);

            pose1[0] = pose1[1] = pose1[2] = SQUAT;
            setPose(pose1);

            for (int i = 0; i < num; i++)
            {
                led[i] = CRGB(random(256), random(256), random(256));
            }
            FastLED.show();
            delay(460);

            _led_normal = true;
            break;
        case 94:
            pose1[0] = LEAN_L;
            pose1[1] = STRECH;
            pose1[2] = LEAN_R;
            setPose(pose1);
            _led_normal = true;
            break;

        default:
            _led_normal = false;
            break;
        }
    }
    if (_led_normal)
    {
        for (int i = 0; i < num; i++)
        {
            led[i] = CRGB(random(256), random(256), random(256));
        }
        FastLED.show();
    }

    return beats;
}