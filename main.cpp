/**
 ******************************************************************************
 *
 *   Copyright (C) 2023, Kulikova Alyona, IU8-11M, variant.5
 *
 ******************************************************************************
 *
 * @name Laboratory No. 5
 *
 * @file main.cpp
 *
 * <b>Modification History</b>
 *
 *   Date        Name        Description
 *
 ******************************************************************************
 * encoding:   UTF-8 BOM
 * tab size:   4
 */

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>

#include <fstream>

using namespace std;

struct point {
    double x, y, f;
};

/**
* @brief _function
* _function sinx * siny / (1 + x^2 + y^2 )
*
* @param x, y
*
* @return result unimodal _functiontion -cos(0.5 * x) - 1
*/
double _function(double x,double y)
{
    return (sin(x) * sin(y) / (1 + pow(x, 2) + pow(y, 2)));
}

bool comparator(point& p1, point& p2) {
    return (p1.f > p2.f);
}

point gen_point(point& p1, point& p2) {
    point buf;
    buf.x = p1.x;
    buf.y = p2.y;
    buf.f = _function(buf.x, buf.y);
    return buf;
}

vector<point> gen_population(vector<point>& population) {
    vector<point> buf(4);
    if (population[0].f == population[1].f) {
        buf[0] = gen_point(population[0], population[2]);
        buf[1] = gen_point(population[2], population[0]);
        buf[2] = gen_point(population[0], population[3]);
        buf[3] = gen_point(population[3], population[0]);
    }
    else {
        double p = rand() / RAND_MAX;
        buf[0] = gen_point(population[0], population[1]);
        buf[1] = gen_point(population[1], population[0]);
        int i, l;
        if (p - 0.5 <= 0) {
            i = 2;
            l = 0;
        }
        else {
            i = 1;
            l = 2;
        }
        buf[2] = gen_point(population[l], population[i]);
        buf[3] = gen_point(population[i], population[l]);
    }
    return buf;
}

double get_mid(vector<point>& pop) {
    double sum = 0;
    for (auto i : pop) {
        sum += i.f;
    }
    return sum / 4;
}

void print_generation(vector<point>& pop, int n) {
    std::ofstream out;
    out.open("TSiSa_lab_5_rk.txt", std::ios::app);
    if (out.is_open())
    {
        out << '\n' << std::string(55, '-') << '\n';
        out << "GENERATION N # " << n
             << "\nMIDDLE = " << get_mid(pop)
             << "\nMAXIMUM = " << pop[0].f << endl;
        for (auto i : pop)
            out << "x:" << std::string(15, ' ') << i.x << std::string(5, ' ')
                 << "y:" << std::string(15, ' ') << i.y << std::string(5, ' ')
                 << "f:" << std::string(15, ' ') << i.f
                 << endl;
    }
    out.close();

//    cout << '\n' << std::string(55, '-') << '\n';
//    cout << "GENERATION N # " << n
//         << "\nMIDDLE = " << get_mid(pop)
//         << "\nMAXIMUM = " << pop[0].f << endl;
//    for (auto i : pop)
//        cout << "x:" << std::string(15, ' ') << i.x << std::string(5, ' ')
//             << "y:" << std::string(15, ' ') << i.y << std::string(5, ' ')
//             << "f:" << std::string(15, ' ') << i.f
//             << endl;
}

#define CONST_A_GENERATION 0.2
#define CONST_B_GENERATION -2.2

int main(){
    // delete
    remove("TSiSa_lab_5_rk.txt");

    int N = 4;
    double a = CONST_A_GENERATION, b = CONST_B_GENERATION;
    srand(time(NULL));
    vector<point> population(4);
    for (int i = 0; i < N; i++) {
        point poi;
        poi.x = (double)(a + rand() * 1. / RAND_MAX * (b - a));
        poi.y = (double)(a + rand() * 1. / RAND_MAX * (b - a));
        poi.f = _function(poi.x, poi.y);
        population[i] = poi;
    }
    sort(population.begin(), population.end(), comparator);
    print_generation(population, 0);
    for (int i = 1; i < 50; i++) {
        double ver = rand() / RAND_MAX;
        if (ver - 0.4 <= 0) {
            point p;
            p.x = (double)(population[0].x + (a + rand() * 1. / RAND_MAX * (b - a)))/2;
            population[0] = gen_point(population[0], p);
            p.y = (double)(population[1].y + (a + rand() * 1. / RAND_MAX * (b - a)))/2;
            population[1] = gen_point(p, population[1]);
            p.x = (double)(population[2].x + (a + rand() * 1. / RAND_MAX * (b - a)))/2;
            population[2] = gen_point(population[2], p);
            p.y = (double)(population[3].y + (a + rand() * 1. / RAND_MAX * (b - a))) / 2;
            population[3] = gen_point(p, population[3]);
        }
        sort(population.begin(), population.end(), comparator);
        vector<point> new_p = gen_population(population);
        population = new_p;
        print_generation(population, i);
    }

    // print result
    std::cout << "\n *** TSiSa_lab_5_rk.txt ***\n" << std::endl;
    std::string line;
    std::ifstream in("TSiSa_lab_5_rk.txt");
    if (in.is_open())
        while (std::getline(in, line))
            std::cout << line << std::endl;
    in.close();
    return 0;
}
