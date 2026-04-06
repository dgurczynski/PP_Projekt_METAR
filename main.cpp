//DOMINIK GURCZYŃSKI 203854 ACIR 2A - Odczyt danych raportow METAR

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

bool get_wind_direction(const char* token) {
    if (strlen(token) == 7 && isalpha(token[3])) {
        for (int i = 0; i < 3; i++) {
            if (!isdigit(token[i])) {
                return false;
            }
        }
        for (int i = 4; i < 7; i++) {
            if (!isdigit(token[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool get_weather(const char* token) {
    if (strcmp(token, "EPGD") != 0 && strlen(token) > 1 && strlen(token) <= 4) {
        int start_index = (token[0] == '-' || token[0] == '+') ? 1 : 0;
        for (int i = start_index; i < strlen(token); i++) {
            if (!isalpha(token[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool get_visibility(const char* token) {
    if (strlen(token) == 4) {
        for (int i = 0; i < 4; i++) {
            if (!isdigit(token[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool get_overcast(const char* token) {
    if (strlen(token) > 5 && strlen(token) < 9) {
        for (int i = 0; i < 3; i++) {
            if (!isalpha(token[i])) {
                return false;
            }
        }
        for (int i = 3; i < 6; i++) {
            if (!isdigit(token[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool get_pressure(const char* token) {
    if (strlen(token) == 5 && token[0] == 'Q') {
        for (int i = 1; i < 5; i++) {
            if (!isdigit(token[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool get_cavok(const char* token) {
    if (strcmp(token, "CAVOK") == 0) {
        return true;
    }
    return false;
}

const char* weather_phenomenon(const char* phenomenon) {
    if (strcmp(phenomenon, "DZ") == 0) return "mzawka";
    if (strcmp(phenomenon, "RA") == 0) return "deszcz";
    if (strcmp(phenomenon, "SN") == 0) return "snieg";
    if (strcmp(phenomenon, "SG") == 0) return "snieg ziarnisty";
    if (strcmp(phenomenon, "IC") == 0) return "slupki lodowe";
    if (strcmp(phenomenon, "GR") == 0) return "grad";
    if (strcmp(phenomenon, "PL") == 0) return "deszcz lodowy";
    if (strcmp(phenomenon, "GS") == 0) return "krupa sniezna/lodowa";
    if (strcmp(phenomenon, "BR") == 0) return "zamglenie";
    if (strcmp(phenomenon, "FG") == 0) return "mgla";
    if (strcmp(phenomenon, "FU") == 0) return "dym";
    if (strcmp(phenomenon, "VA") == 0) return "popiol wulkaniczny";
    if (strcmp(phenomenon, "SA") == 0) return "piasek";
    if (strcmp(phenomenon, "HZ") == 0) return "zmetnienie";
    if (strcmp(phenomenon, "DU") == 0) return "pyl";
    if (strcmp(phenomenon, "SQ") == 0) return "nawalnica";
    if (strcmp(phenomenon, "FC") == 0) return "traba powietrzna";
    if (strcmp(phenomenon, "DS") == 0) return "burza pylowa";
    if (strcmp(phenomenon, "PO") == 0) return "silnie rozwiniete wiry pylowe";
    if (strcmp(phenomenon, "SS") == 0) return "burza piaskowa";
    return "nie znaleziono";
}

const char* clouds_intensity(const char* intensity) {
    if (strcmp(intensity, "SKC") == 0) return "0/8";
    if (strcmp(intensity, "FEW") == 0) return "1/8 - 2/8";
    if (strcmp(intensity, "SCT") == 0) return "3/8 - 4/8";
    if (strcmp(intensity, "BKN") == 0) return "5/8 - 7/8";
    if (strcmp(intensity, "OVC") == 0) return "8/8";
    return "nie znaleziono";
}

int main() {
    bool game_on = true;

    while (game_on) {
        char user_input;

        std::cout << "Witaj DOMINIK GURCZYNSKI 203854 w programie analizy raportow METAR\n";
        std::cout << "===== MENU =====" << std::endl;
        std::cout << "* Nacisnij q, jesli chcesz zakonczyc dzialanie programu.\n";
        std::cout << "* Nacisnij o, zeby wyświetlic dane pogodowe.\n";
        std::cout << "Podaj swoj wybor: ";
        std::cin >> user_input;
        std::cout << "\n";

        if (user_input == 'q') {
            std::cout << "Dzialanie programu zostalo zakonczone!" << std::endl;
            game_on = false;
        }
        else if (user_input == 'o') {
            std::ifstream read_file("C:/Users/domin/Desktop/Metar_Gdansk1.txt");
            std::ofstream save_file("C:/Users/domin/Desktop/pogoda_gd.txt");

            if (!read_file || !save_file) {
                std::cout << "Nie udalo sie otworzyc pliku!" << std::endl;
                return 1;
            }

            char line[100];
            char overcast_list[3][9];
            char phenomenons_list[3][6];
            int overcast_count = 0;
            int phenomenon_count = 0;
            int counter = 0;

            char airport[5], date[3], time[6], bearing[4], wind_speed[3], gust_speed[3], temp[3], pressure[5], visibility[5], dew_temp[5], overcast[7], wind_direction1[4], wind_direction2[4], weather[5], overcast_intensity[4], overcast_height[4];

            while (read_file.getline(line, sizeof(line))) {
                counter++;

                strncpy_s(airport, sizeof(airport), line, 4);
                if (strcmp(airport, "EPGD") == 0) {
                    overcast_count = 0;
                    phenomenon_count = 0;
                    memset(overcast_list, 0, sizeof(overcast_list));
                    memset(phenomenons_list, 0, sizeof(phenomenons_list));

                    strncpy_s(date, sizeof(date), line + 5, 2);
                    strncpy_s(time, sizeof(time), line + 7, 2);
                    time[2] = ':';
                    strncpy_s(time + 3, sizeof(time) - 3, line + 9, 2);
                    strncpy_s(bearing, sizeof(bearing), line + 13, 3);
                    strncpy_s(wind_speed, sizeof(wind_speed), line + 16, 2);
                    strncpy_s(gust_speed, sizeof(gust_speed), line + 19, 2);

                    char* context = nullptr;
                    char* token = strtok_s(line, " ", &context);
                    bool wind_direction_found = false;
                    bool weather_found = false;
                    bool cavok_found = false;

                    while (token != nullptr) {
                        if (strchr(token, '/') && strlen(token) <= 6) {
                            strncpy_s(temp, sizeof(temp), token, 2);
                            strncpy_s(dew_temp, sizeof(dew_temp), token + 3, 3);
                        }
                        else if (get_wind_direction(token)) {
                            strncpy_s(wind_direction1, sizeof(wind_direction1), token, 3);
                            strncpy_s(wind_direction2, sizeof(wind_direction2), token + 4, 3);
                            wind_direction_found = true;
                        }
                        else if (get_pressure(token)) {
                            if (token[1] == '0') {
                                strncpy_s(pressure, sizeof(pressure), token + 2, 3);
                            }
                            else {
                                strncpy_s(pressure, sizeof(pressure), token + 1, 4);
                            }
                        }
                        else if (get_weather(token) && phenomenon_count < 3) {
                            strncpy_s(phenomenons_list[phenomenon_count], sizeof(phenomenons_list[phenomenon_count]), token, strlen(token));
                            phenomenon_count++;
                            weather_found = true;
                        }
                        else if (get_cavok(token)) {
                            cavok_found = true;
                        }
                        else if (get_visibility(token)) {
                            strncpy_s(visibility, sizeof(visibility), token, 4);
                        }
                        else if (get_overcast(token) && overcast_count < 3) {
                            strncpy_s(overcast_list[overcast_count], sizeof(overcast_list[overcast_count]), token, 9);
                            overcast_count++;
                        }
                        token = strtok_s(nullptr, " ", &context);
                    }

                    int month;

                    if (strcmp(date, "29") == 0 || strcmp(date, "30") == 0) {
                        month = 11;
                    }
                    else {
                        month = 12;
                    }

                    if (counter <= 3) {
                        std::cout << "Data: " << date << "." << month << ".2024" << std::endl;
                        std::cout << "Czas UTC: " << time << std::endl;
                    }

                    save_file << "Data: " << date << "." << month << ".2024" << std::endl;
                    save_file << "Czas UTC: " << time << std::endl;

                    if (wind_direction_found) {
                        if (counter <= 3) {
                            std::cout << "Wiatr: z kierunku " << bearing << " stopni, zmienny od " << wind_direction1 << " do " << wind_direction2 << ", predkosc " << wind_speed << " kts" << std::endl;
                        }

                        save_file << "Wiatr: z kierunku " << bearing << " stopni, zmienny od " << wind_direction1 << " do " << wind_direction2 << ", predkosc " << wind_speed << " kts" << std::endl;
                    }
                    else {
                        if (counter <= 3) {
                            std::cout << "Wiatr: z kierunku " << bearing << " stopni, predkosc " << wind_speed << " kts" << std::endl;
                        }

                        save_file << "Wiatr: z kierunku " << bearing << " stopni, predkosc " << wind_speed << " kts" << std::endl;
                    }
                    if (weather_found) {
                        for (int i = 0; i < phenomenon_count; ++i) {
                            char intensity[11] = "";
                            if (phenomenons_list[i][0] == '+') {
                                strncpy_s(intensity, sizeof(intensity), "intensywny ", 11);
                                if (counter <= 3) {
                                    std::cout << "Aktualne zjawiska pogodowe: " << intensity << weather_phenomenon(phenomenons_list[i] + 1) << std::endl;
                                }

                                save_file << "Aktualne zjawiska pogodowe: " << intensity << weather_phenomenon(phenomenons_list[i] + 1) << std::endl;
                            }
                            else if (phenomenons_list[i][0] == '-') {
                                strncpy_s(intensity, sizeof(intensity), "lekki ", 8);
                                if (counter <= 3) {
                                    std::cout << "Aktualne zjawiska pogodowe: " << intensity << weather_phenomenon(phenomenons_list[i] + 1) << std::endl;
                                }

                                save_file << "Aktualne zjawiska pogodowe: " << intensity << weather_phenomenon(phenomenons_list[i] + 1) << std::endl;
                            }
                            else {
                                if (counter <= 3) {
                                    std::cout << "Aktualne zjawiska pogodowe: " << weather_phenomenon(phenomenons_list[i]) << std::endl;
                                }

                                save_file << "Aktualne zjawiska pogodowe: " << weather_phenomenon(phenomenons_list[i]) << std::endl;
                            }
                        }
                    }
                    if (counter <= 3) {
                        std::cout << "temperatura: " << temp << " C, temperatura rosy: " << dew_temp << " C" << std::endl;
                        std::cout << "cisnienie atmosferyczne: " << pressure << " hPa" << std::endl;
                    }

                    save_file << "temperatura: " << temp << " C, temperatura rosy: " << dew_temp << " C" << std::endl;
                    save_file << "cisnienie atmosferyczne: " << pressure << " hPa" << std::endl;

                    if (cavok_found) {
                        if (counter <= 3) {
                            std::cout << "Widocznosc w metrach: 10000 lub wiecej, brak chmur ponizej 1500 metrow" << std::endl;
                        }

                        save_file << "Widocznosc w metrach: 10000 lub wiecej, brak chmur ponizej 1500 metrow" << std::endl;
                    }
                    else if (strcmp(visibility, "9999") == 0) {
                        if (counter <= 3) {
                            std::cout << "Widocznosc w metrach: 10000 lub wiecej" << std::endl;
                        }

                        save_file << "Widocznosc w metrach: 10000 lub wiecej" << std::endl;
                    }
                    else {
                        if (counter <= 3) {
                            std::cout << "Widocznosc w metrach: " << visibility << std::endl;
                        }

                        save_file << "Widocznosc w metrach: " << visibility << std::endl;
                    }

                    for (int i = 0; i < overcast_count; ++i) {
                        strncpy_s(overcast_intensity, sizeof(overcast_intensity), overcast_list[i], 3);
                        strncpy_s(overcast_height, sizeof(overcast_height), overcast_list[i] + 3, 3);

                        if (counter <= 3) {
                            std::cout << clouds_intensity(overcast_intensity) << " chmur na wysokosci " << atoi(overcast_height) * 30 << " ft" << std::endl;
                        }

                        save_file << clouds_intensity(overcast_intensity) << " chmur na wysokosci " << atoi(overcast_height) * 30 << " ft" << std::endl;
                    }
                    if (counter <= 3) {
                        std::cout << "\n" << std::endl;
                    }

                    save_file << "\n" << std::endl;
                }
            }
            read_file.close();
            save_file.close();
        }
        else {
            std::cout << "Podano niewlasciwy wybor!" << std::endl;
        }
    }

    return 0;
}
