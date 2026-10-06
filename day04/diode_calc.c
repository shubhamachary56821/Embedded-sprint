#include <stdio.h>
#include <stddef.h>

/* Standard E12 resistor values (ohms), one decade */
static const double E12[] = {10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82};

/* Smallest standard resistor >= r_ohm (safe side for LED current) */
double next_standard(double r_ohm) {
    double scale = 1.0;
    while (r_ohm / scale >= 100.0) scale *= 10.0;
    while (r_ohm / scale < 10.0)   scale /= 10.0;
    for (size_t i = 0; i < sizeof(E12) / sizeof(E12[0]); i++)
        if (E12[i] * scale >= r_ohm) return E12[i] * scale;
    return 10.0 * 10.0 * scale;          /* roll into next decade */
}

/* R = (Vsupply - Vled) / I */
double led_resistor(double vs, double vf, double i_amp) {
    return (vs - vf) / i_amp;
}

/* Ripple voltage on a smoothing capacitor: dV = I / (f * C) */
double ripple(double i_amp, double f_hz, double c_farad) {
    return i_amp / (f_hz * c_farad);
}

int main(void) {
    double r = led_resistor(3.3, 2.0, 0.010);
    double std = next_standard(r);
    printf("LED: need %.1f ohm -> use %.0f ohm -> I = %.2f mA\n",
           r, std, (3.3 - 2.0) / std * 1000.0);

    r = led_resistor(5.0, 3.0, 0.020);
    std = next_standard(r);
    printf("LED: need %.1f ohm -> use %.0f ohm -> I = %.2f mA\n",
           r, std, (5.0 - 3.0) / std * 1000.0);

    printf("Half-wave ripple (50 Hz, 10 mA, 100 uF): %.2f V\n",
           ripple(0.010, 50.0, 100e-6));
    printf("Full-wave ripple (100 Hz, 10 mA, 100 uF): %.2f V\n",
           ripple(0.010, 100.0, 100e-6));
    return 0;
}