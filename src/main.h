//
// Created by lena on 2/5/24.
//
#pragma once
#include "config.h"

uint make_module(const std::string& filepath, uint module_type);
uint make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
