#include <iostream>
#include <string>
#include <vector>
#include <cmath>

enum Outlook { sunny, overcast, rain, OUTLOOK_NUM_ITEMS };
enum Temperature { cool, mild, hot, TEMPERATURE_NUM_ITEMS };
enum Humidity { normal, high, HUMIDITY_NUM_ITEMS };
enum Wind { weak, strong, WIND_NUM_ITEMS };
enum PlayTennis { no, yes, PLAYTENNIS_NUM_ITEMS };

struct record_t {
    Outlook outlook;
    Temperature temperature;
    Humidity humidity;
    Wind wind;
    PlayTennis play_tennis;
} records[14];

void populate_records() {
    // 1
    records[0].outlook = sunny;
    records[0].temperature = hot;
    records[0].humidity = high;
    records[0].wind = weak;
    records[0].play_tennis = no;

    // 2
    records[1].outlook = sunny;
    records[1].temperature = hot;
    records[1].humidity = high;
    records[1].wind = strong;
    records[1].play_tennis = no;

    // 3
    records[2].outlook = overcast;
    records[2].temperature = hot;
    records[2].humidity = high;
    records[2].wind = weak;
    records[2].play_tennis = yes;

    // 4
    records[3].outlook = rain;
    records[3].temperature = mild;
    records[3].humidity = high;
    records[3].wind = weak;
    records[3].play_tennis = yes;

    // 5
    records[4].outlook = rain;
    records[4].temperature = cool;
    records[4].humidity = normal;
    records[4].wind = weak;
    records[4].play_tennis = yes;

    // 6
    records[5].outlook = rain;
    records[5].temperature = cool;
    records[5].humidity = normal;
    records[5].wind = strong;
    records[5].play_tennis = no;

    // 7
    records[6].outlook = overcast;
    records[6].temperature = cool;
    records[6].humidity = normal;
    records[6].wind = strong;
    records[6].play_tennis = yes;

    // 8
    records[7].outlook = sunny;
    records[7].temperature = mild;
    records[7].humidity = high;
    records[7].wind = weak;
    records[7].play_tennis = no;

    // 9
    records[8].outlook = sunny;
    records[8].temperature = cool;
    records[8].humidity = normal;
    records[8].wind = weak;
    records[8].play_tennis = yes;

    // 10
    records[9].outlook = rain;
    records[9].temperature = mild;
    records[9].humidity = normal;
    records[9].wind = weak;
    records[9].play_tennis = yes;

    // 11
    records[10].outlook = sunny;
    records[10].temperature = mild;
    records[10].humidity = normal;
    records[10].wind = strong;
    records[10].play_tennis = yes;

    // 12
    records[11].outlook = overcast;
    records[11].temperature = mild;
    records[11].humidity = high;
    records[11].wind = strong;
    records[11].play_tennis = yes;

    // 13
    records[12].outlook = overcast;
    records[12].temperature = hot;
    records[12].humidity = normal;
    records[12].wind = weak;
    records[12].play_tennis = yes;

    // 14
    records[13].outlook = rain;
    records[13].temperature = mild;
    records[13].humidity = high;
    records[13].wind = strong;
    records[13].play_tennis = no;
}

int main() {
    std::cout << "Training data:" << std::endl;

    populate_records();

    double pos = 0;
    double neg = 0;

    for (int i = 0; i < 14; ++i) {
        std::cout << "<" << records[i].outlook
                  << "," << records[i].temperature
                  << "," << records[i].humidity
                  << "," << records[i].wind
                  << "," << records[i].play_tennis
                  << ">" << std::endl;

        switch (records[i].play_tennis) {
            case no:
                neg += 1.0;
                break;
            case yes:
                pos += 1.0;
                break;
            default:
                break;
        }
    }

    double pos_r = pos / (pos + neg);
    double neg_r = neg / (pos + neg);

    double entropy = -1.0 * pos_r * log2(pos_r) +
                     -1.0 * neg_r * log2(neg_r);

    std::cout << entropy << std::endl;

    // Information gain for wind.
    double gain_wind;
    double wind_pos[WIND_NUM_ITEMS];
    double wind_neg[WIND_NUM_ITEMS];
    for (int i = 0; i < WIND_NUM_ITEMS; ++i)
        wind_pos[i] = 0.0;

    for (int j = 0; j < 14; ++j)
        switch (records[j].play_tennis) {
            case no:
                wind_neg[records[j].wind] += 1.0;
                break;
            case yes:
                wind_pos[records[j].wind] += 1.0;
                break;
            default:
                break;
        }
    
    gain_wind = entropy;
    for (int k = 0; k < WIND_NUM_ITEMS; ++k) {
        double wind_pos_v_r = wind_pos[k] / (wind_pos[k] + wind_neg[k]);
        double wind_neg_v_r = wind_neg[k] / (wind_pos[k] + wind_neg[k]);
        double wind_v_entropy = -1.0 * wind_pos_v_r * log2(wind_pos_v_r) +
                                -1.0 * wind_neg_v_r * log2(wind_neg_v_r);

        std::cout << wind_v_entropy << std::endl;

        gain_wind -= wind_v_entropy * (wind_pos[k] + wind_neg[k]) / 14.0;
    }

    std::cout << gain_wind << std::endl;
    
    return 0;
}