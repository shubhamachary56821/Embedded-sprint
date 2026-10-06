#include <stdio.h>
#include <stddef.h>

static const double E12[] = {10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82};

/* Largest standard resistor <= r_ohm (base resistor: round DOWN so the
   transistor is driven at least as hard as calculated). */
double prev_standard(double r_ohm) {
    double scale = 1.0;
    while (r_ohm / scale >= 100.0) scale *= 10.0;
    while (r_ohm / scale < 10.0)   scale /= 10.0;
    double best = 10.0 * scale / 10.0;
    for (size_t i = 0; i < sizeof(E12) / sizeof(E12[0]); i++)
        if (E12[i] * scale <= r_ohm) best = E12[i] * scale;
    return best;
}

/* BJT as a switch: drive it into saturation using a forced beta of ~10.
   Ib = Ic / beta_forced,  Rb = (Vgpio - Vbe) / Ib */
double bjt_base_resistor(double v_gpio, double ic_amp, double beta_forced) {
    double ib = ic_amp / beta_forced;
    return (v_gpio - 0.7) / ib;
}

/* MOSFET as a switch: conduction loss P = I^2 * Rds(on) */
double mosfet_loss_w(double i_amp, double rds_on_ohm) {
    return i_amp * i_amp * rds_on_ohm;
}

/* Resistor divider output */
double divider(double vin, double r_top, double r_bottom) {
    return vin * r_bottom / (r_top + r_bottom);
}

int main(void) {
    /* Relay coil needs 70 mA, driven from a 3.3 V GPIO via an NPN BJT */
    double rb = bjt_base_resistor(3.3, 0.070, 10.0);
    double use = prev_standard(rb);
    printf("BJT: base resistor calc %.0f ohm -> use %.0f ohm -> Ib = %.2f mA\n",
           rb, use, (3.3 - 0.7) / use * 1000.0);

    /* Motor draws 2 A through a MOSFET with Rds(on) = 0.05 ohm vs 0.5 ohm */
    printf("MOSFET loss at 2 A: Rds=0.05 -> %.2f W,  Rds=0.5 -> %.2f W\n",
           mosfet_loss_w(2.0, 0.05), mosfet_loss_w(2.0, 0.5));

    /* 5 V sensor into a 3.3 V ADC pin: pick a divider and check it */
    double vout = divider(5.0, 10000.0, 20000.0);
    printf("Divider 10k/20k from 5 V -> %.2f V (ADC safe if <= 3.3 V)\n", vout);

    /* 10-bit ADC, 3.3 V reference: size of one LSB */
    printf("10-bit ADC LSB at 3.3 V: %.2f mV\n", 3.3 / 1024.0 * 1000.0);
    return 0;
}