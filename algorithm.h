#pragma once
#include <iostream>
#include <vector>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>
#include <typeinfo>

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

class Algorithms {
public:
#include <glm/glm.hpp> // Include the glm library for glm::vec2 and glm::vec3

    static std::vector<Vertex> dda(float x_1, float y_1, float x_2, float y_2) {
        std::vector<Vertex> coordinates;
        float m, dx, dy;
        int current_steps = 0;
        int steps;

        float scaling_factor_x = std::fmax(x_1, x_2);  // Scale x
        float scaling_factor_y = std::fmax(y_1, y_2);  // Scale y

        dx = x_2 - x_1;
        dy = y_2 - y_1;
        m=dy/dx;

        if (std::fabs(dx) > std::fabs(dy)) {
            steps = std::fabs(dx);
        } else {
            steps = std::fabs(dy);
        }
        coordinates.push_back({{std::roundf(x_1) / scaling_factor_x, std::roundf(y_1) / scaling_factor_y}, {0.0f, 0.0f, 1.0f}});

        current_steps = 1;
        for (current_steps = 1; current_steps <= steps; current_steps++) {
            if (m < 1) {
                x_1 = 1 + x_1;
                y_1 = m + y_1;
            } else if (m > 1) {
                x_1 = (1 / m) + x_1;
                y_1 = 1 + y_1;
            } else {
                x_1 = 1 + x_1;
                y_1 = 1 + y_1;
            }

            coordinates.push_back({{std::roundf(x_1) / scaling_factor_x, std::roundf(y_1) / scaling_factor_y}, {0.0f, 0.0f, 1.0f}});
        }

        return coordinates;
    }
    static std::vector<Vertex> bresenhem_algorithm(float x_1, float y_1, float x_2, float y_2) {
        float m, p_k;
        float dx, dy;
        int current_steps=0;
        std::vector<Vertex> coordinates;

        float scaling_factor_x = std::fmax(x_1, x_2);  // Scale x
        float scaling_factor_y = std::fmax(y_1, y_2);  // Scale y

        dx = x_2 - x_1;
        dy = y_2 - y_1;
        m = dy / dx;


        p_k = 2 * dy - dx;

        std::cout << "( X1 : " << x_1 << ", Y1: " << y_1 << ")" << "( X2 : " << x_2 << ", Y2: " << y_2 << ")" << std::endl;
        std::cout << "Dy : " <<  dy << " Dx : " << dx <<  "M : " << m << std::endl;

        while (x_1 <= x_2 && y_1 <= y_2) {
            std::cout << "(" << x_1 << ", " << y_1 << ")" << std::endl;
            coordinates.push_back({{std::roundf(x_1) / scaling_factor_x, std::roundf(y_1) / scaling_factor_y}, {0.0f, 0.0f, 1.0f}});

            if (p_k < 0) {
                p_k += 2 * dy;
                x_1 = x_1 + 1;
            } else if (p_k >= 0) {
                p_k += (2 * dy - 2 * dx);
                x_1 = x_1 + 1;
                y_1 = y_1 + 1;
            }
            current_steps += 1;
        }


        // Add vertices for x-axis line
        coordinates.push_back({{0.0f, 0.5f}, {1.0f, 1.0f, 1.0f}});
        coordinates.push_back({{1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}});

        // Add vertices for y-axis line
        coordinates.push_back({{0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}});
        coordinates.push_back({{0.5f, 1.0f}, {1.0f, 1.0f, 1.0f}});

        return coordinates;
    }

    static std::vector<Vertex> bresenham_algorithm2(float x_1, float y_1, float x_2, float y_2) {
        std::vector<Vertex> coordinates;
        float m, dx, dy,  p_k,x,y;
        int current_steps = 0;
        int steps;
        int step,incx, incy;

        float scaling_factor_x = std::fmax(x_1, x_2);  // Scale x
        float scaling_factor_y = std::fmax(y_1, y_2);  // Scale y

        dx = std::abs( x_2 - x_1);
        dy = std::abs (y_2 - y_1);
        m=dy/dx;

        std::cout << "( X1 : " << x_1 << ", Y1: " << y_1 << ")" << "( X2 : " << x_2 << ", Y2: " << y_2 << ")" << std::endl;
        std::cout << "Dy : " <<  dy << " Dx : " << dx <<  "M : " << m << std::endl;

        incx = 1;
        if (x_2 < x_1) incx = -1;
        incy = 1;
        if (y_2 < y_1) incy = -1;

        if (dx > dy) {
            step = dx;
        } else {
            step = dy;
        }

        x = x_1;
        y = y_1;

        coordinates.push_back({{std::roundf(x) / scaling_factor_x, std::roundf(y) / scaling_factor_y}, {0.0f, 0.0f, 1.0f}});


        p_k = 2 * dy - dx;

        for (int i = 0; i < step; i++) {
            std::cout << "(" << x << ", " << y << ")" << std::endl;
            if (p_k < 0) {
                x += incx;
                p_k += 2 * dy;
            } else {
                x += incx;
                y += incy;
                p_k += 2 * (dy - dx);
            }

            coordinates.push_back({{std::roundf(x) / scaling_factor_x, std::roundf(y) / scaling_factor_y}, {0.0f, 0.0f, 1.0f}});

        }
        return coordinates;
    }

};