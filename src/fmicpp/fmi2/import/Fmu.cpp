/*
 * The MIT License
 *
 * Copyright 2017-2018 Norwegian University of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <fmicpp/fmi2/import/Fmu.hpp>

using namespace std;
using namespace fmicpp::fmi2::import;

namespace fs = boost::filesystem;

Fmu::Fmu(const std::string &fmu_path) {

    this->tmp_path_ = fs::temp_directory_path() /= fs::path(fmu_path).stem();
    create_directories(tmp_path_);

    string modelDescriptionPath = tmp_path_.string() + "/modelDescription.xml";

    this->modelDescription_ = make_unique<ModelDescription>(ModelDescription());
    this->modelDescription_->load(modelDescriptionPath);

    ifstream t(modelDescriptionPath);
    this->model_description_xml_ = string((istreambuf_iterator<char>(t)),
                                          istreambuf_iterator<char>());

}

const ModelDescription &Fmu::getModelDescription() const {
    return *modelDescription_;
}

const string &Fmu::getModelDescriptionXml() const {
    return model_description_xml_;
}

Fmu::~Fmu() {
    remove_all(this->tmp_path_);
}
