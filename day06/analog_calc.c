#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define PI 3.14159265358979

/* Voltage divider output */
double divider(double vin, double r1, double r2) { return vin * r2 / (r1 + r2); }

/* RC time constant (seconds) and low-pass cutoff (Hz) */
double rc_tau(double r, double c)        { return r * c; }
double rc_cutoff(double r, double c)     { return 1.0 / (2.0 * PI * r * c); }

/* Capacitor voltage while charging through R from a step of vin, at time t */
double rc_charge(double vin, double r, double c, double t) {
    return vin * (1.0 - exp(-t / (r * c)));
}

/* Ideal op-amp gains */
double noninv_gain(double rf, double rg) { return 1.0 + rf / rg; }
double inv_gain(double rf, double rin)   { return -rf / rin; }

/* ADC helpers */
double adc_lsb(double vref, int bits)    { return vref / (double)(1u << bits); }
uint32_t adc_code(double vin, double vref, int bits) {
    double c = vin / adc_lsb(vref, bits);
    uint32_t max = (1u << bits) - 1u;
    if (c < 0) return 0;
    return c > max ? max : (uint32_t)c;
}
double adc_to_volts(uint32_t code, double vref, int bits) {
    return code * adc_lsb(vref, bits);
}

/* Nyquist: sampling must be more than 2x the highest signal frequency */
int nyquist_ok(double f_signal, double f_sample) { return f_sample > 2.0 * f_signal; }

int main(void) {
    printf("--- Divider ---\n");
    double v = divider(5.0, 10000.0, 18000.0);
    printf("5 V via 10k/18k -> %.2f V (%s for a 3.3 V ADC)\n",
           v, v <= 3.3 ? "safe" : "TOO HIGH");

    printf("--- RC ---\n");
    printf("10k, 1uF: tau = %.1f ms, 5*tau = %.1f ms\n",
           rc_tau(10e3, 1e-6) * 1e3, 5 * rc_tau(10e3, 1e-6) * 1e3);
    printf("1k, 100nF: cutoff = %.0f Hz\n", rc_cutoff(1e3, 100e-9));
    printf("after 1 tau: %.0f%% of Vin\n",
           rc_charge(1.0, 10e3, 1e-6, 10e-3) * 100.0);

    printf("--- Op-amp ---\n");
    printf("non-inverting Rf=40k Rg=10k: gain = %.1f\n", noninv_gain(40e3, 10e3));
    printf("inverting Rf=20k Rin=10k: gain = %.1f\n", inv_gain(20e3, 10e3));

    printf("--- ADC ---\n");
    printf("10-bit, 3.3 V: LSB = %.2f mV\n", adc_lsb(3.3, 10) * 1e3);
    printf("12-bit, 3.3 V: LSB = %.2f mV\n", adc_lsb(3.3, 12) * 1e3);
    uint32_t code = adc_code(1.65, 3.3, 10);
    printf("1.65 V -> code %u -> back to %.3f V\n",
           code, adc_to_volts(code, 3.3, 10));
    printf("5 kHz tone sampled at 8 kHz: %s\n",
           nyquist_ok(5000, 8000) ? "OK" : "ALIASING");
    printf("5 kHz tone sampled at 20 kHz: %s\n",
           nyquist_ok(5000, 20000) ? "OK" : "ALIASING");
    return 0;
}