#include <stdio.h>

#include <SFML/Graphics.hpp>

#define IX(i,j) ((i)+(N+2)*(j))
#define SWAP(x0,x) {double *tmp=x0;x0=x;x=tmp;}
#define N 100
#define V_SIZE (N + 2)*(N + 2)

#define WINDOW_SIZE 400

double *sources, *u_sources, *v_sources;
double *vel_u, *vel_v, *prev_vel_u, *prev_vel_v;
double *densities, *prev_densities;

void add_sources (double *x, double *s, double dt)
{
    for (int i = 0; i < V_SIZE; i++) x[i] += s[i]*dt;
}

void diffuse (double *x, double *x0, double diff, double dt)
{
    double a = dt*diff*N*N;

    for (int k = 0; k < 20; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
                x[IX(i, j)] = (x0[IX(i, j)] +
                        a*(x[IX(i - 1, j)] + x[IX(i, j - 1)] +
                            x[IX(i + 1, j)] + x[IX(i, j + 1)]))/(1 + 4*a);
        }
    }
}

void advect (double *d, double *d0, double *u, double *v, double dt)
{
    int i0, i1, j0, j1;
    double s0, s1, t0, t1;
    double dt0 = dt*N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            double x = i - dt0*u[IX(i, j)];
            double y = j - dt0*v[IX(i, j)];

            if (x < .5) x = .5;
            if (y < .5) y = .5;

            if (x > N + .5) x = N + .5;
            if (y > N + .5) y = N + .5;

            i0 = (int) x;
            j0 = (int) y;

            i1 = i0 + 1;
            j1 = j0 + 1;

            s1 = x - i0;
            s0 = 1 - s1;
            t1 = y - j0;
            t0 = 1 - t1;

            d[IX(i, j)] = s0*(t0*d0[IX(i0, j0)] + t1*d0[IX(i0, j1)]) +
                s1*(t0*d0[IX(i1, j0)] + t1*d0[IX(i1, j1)]);
        }
    }
}

void project (double *u, double *v, double *p, double *div)
{
    double h = 1.0/N;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            div[IX(i, j)] = -0.5*h*(u[IX(i + 1, j)] - u[IX(i - 1, j)] +
                    v[IX(i, j + 1)] + v[IX(i, j - 1)]);
            p[IX(i, j)] = 0;
        }
    }


    for (int k = 0; k < 20; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                p[IX(i, j)] = (div[IX(i, j)] + p[IX(i + 1, j)] + p[IX(i - 1, j)] +
                        p[IX(i, j + 1)] + p[IX(i, j - 1)])/4;
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            //u[IX(i, j)] -= p[IX(i + 1, j)] - p[IX(i - 1, j)];
            //v[IX(i, j)] -= p[IX(i, j + 1)] - p[IX(i, j - 1)]/h;
            u[IX(i, j)] -= 0.5*(p[IX(i + 1, j)] - p[IX(i - 1, j)])/h;
            v[IX(i, j)] -= 0.5*(p[IX(i, j + 1)] - p[IX(i, j - 1)])/h;
        }
    }

}

void dens_step(double *x, double *x0, double *srcs, double *u, double *v, double diff, double dt)
{
    add_sources(x, srcs, dt);
    SWAP(x0, x);
    diffuse(x, x0, diff, dt);
    SWAP(x0, x);
    advect(x, x0, u, v, dt);
}

void vel_step(double *u, double *v, double *u0, double *v0, double *usrc, double *vsrc, double visc, double dt)
{
    add_sources(u, usrc, dt);
    add_sources(v, vsrc, dt);
    SWAP(u0, u);
    diffuse(u, u0, visc, dt);
    SWAP(v0, v);
    diffuse(v, v0, visc, dt);

    project(u, v, u0, v0);

    SWAP(u0, u);
    SWAP(v0, v);

    advect (u, u0, u0, v0, dt);
    advect (v, v0, u0, v0, dt);
    project(u, v, u0, v0);
}

int main()
{
    sources = new double[V_SIZE];
    u_sources = new double[V_SIZE];
    v_sources = new double[V_SIZE];
    prev_vel_u = new double[V_SIZE];
    prev_vel_v = new double[V_SIZE];
    vel_u = new double[V_SIZE];
    vel_v = new double[V_SIZE];
    densities = new double[V_SIZE];
    prev_densities = new double[V_SIZE];

    sources[IX(50, 50)] = 10000;
    v_sources[IX(5, 5)] = 10;

    for (int i = 0; i < V_SIZE; i++)
        vel_u[i] = vel_v[i] = -.2;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Fluids");

    sf::Clock clock;

    add_sources(densities, sources, 1);

    while (window.isOpen())
    {
        sf::Event evn;
        while (window.pollEvent(evn))
        {
            if (evn.type == sf::Event::Closed)
                window.close();
        }

        double dt = clock.restart().asSeconds();

        vel_step(vel_u, vel_v, prev_vel_u, prev_vel_v, u_sources, v_sources, .1, dt);
        dens_step(densities, prev_densities, sources, vel_u, vel_v, .0005, dt);
        window.clear();

        double tile_size = WINDOW_SIZE/N;

        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(tile_size, tile_size));

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                double col = densities[IX(i, j)];
                if (col > 255)
                    col = 255;
                shape.setPosition((i - 1)*tile_size, (j - 1)*tile_size);
                shape.setFillColor(sf::Color(col, col, col));
                window.draw(shape);
            }
        }

        window.display();
    }
}
