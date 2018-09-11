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

#ifndef FMICPP_COSIMULATIONSLAVE_HPP
#define FMICPP_COSIMULATIONSLAVE_HPP

#include <memory>
#include "FmuSlave.hpp"
#include "AbstractFmuInstance.hpp"
#include "CoSimulationLibrary.hpp"

#include "../xml/ModelDescription.hpp"

namespace fmicpp::fmi2::import {

    using xml::CoSimulationModelDescription;

    class CoSimulationSlave: public FmuSlave,
            public AbstractFmuInstance<CoSimulationLibrary, CoSimulationModelDescription>  {

    public:
        explicit CoSimulationSlave(const fmi2Component c,
                const std::shared_ptr<CoSimulationModelDescription> modelDescription,
                const std::shared_ptr<CoSimulationLibrary> library);

        fmi2Status doStep(const double stepSize) override;

        fmi2Status cancelStep() override;

        const CoSimulationModelDescription &getModelDescription() const override;

        void init(const double start = 0, const double stop = 0) override;

        fmi2Status reset() override;

        fmi2Status terminate() override;

        bool canGetAndSetFMUstate() const override;

        fmi2Status getFMUstate(fmi2FMUstate &state) override;

        fmi2Status setFMUstate(const fmi2FMUstate state) override;

        fmi2Status freeFMUstate(fmi2FMUstate &state) override;

        bool canSerializeFmuState() const override;

        fmi2Status serializeFMUstate(const fmi2FMUstate &state, vector<fmi2Byte> &serializedState) override;

        fmi2Status deSerializeFMUstate(fmi2FMUstate &state, const vector<fmi2Byte> &serializedState) override;

        bool providesDirectionalDerivative() const override;

        fmi2Status getDirectionalDerivative(const vector<fmi2ValueReference> &vUnkownRef,
                                            const vector<fmi2ValueReference> &vKnownRef,
                                            const vector<fmi2Real> &dvKnownRef,
                                            vector<fmi2Real> &dvUnknownRef) const override;

        fmi2Status readInteger(const fmi2ValueReference vr, fmi2Integer &ref) const override;

        fmi2Status readInteger(const vector<fmi2ValueReference> &vr, vector<fmi2Integer> &ref) const override;

        fmi2Status readReal(const fmi2ValueReference vr, fmi2Real &ref) const override;

        fmi2Status readReal(const vector<fmi2ValueReference> &vr, vector<fmi2Real> &ref) const override;

        fmi2Status readString(const fmi2ValueReference vr, fmi2String &ref) const override;

        fmi2Status readString(const vector<fmi2ValueReference> &vr, vector<fmi2String> &ref) const override;

        fmi2Status readBoolean(const fmi2ValueReference vr, fmi2Boolean &ref) const override;

        fmi2Status readBoolean(const vector<fmi2ValueReference> &vr, vector<fmi2Boolean> &ref) const override;

    };

}


#endif //FMICPP_COSIMULATIONSLAVE_HPP
