#include "../include/cylinder_head.h"

#include "../include/cylinder_bank.h"

#include <assert.h>

CylinderHead::CylinderHead() {
    m_exhaustSystems = nullptr;
    m_intakes = nullptr;

    m_flipDisplay = false;

    m_bank = nullptr;
    m_exhaustCamshaft = nullptr;
    m_intakeCamshaft = nullptr;

    m_exhaustPortFlow = nullptr;
    m_intakePortFlow = nullptr;

    m_flow = 1.0;
    m_combustionChamberVolume = 0.0;
}

CylinderHead::~CylinderHead() {
    /* void */
}

void CylinderHead::initialize(const Parameters &params) {
    m_exhaustSystems = new ExhaustSystem *[params.Bank->m_cylinderCount];
    m_intakes = new Intake *[params.Bank->m_cylinderCount];

    m_bank = params.Bank;
    m_exhaustCamshaft = params.ExhaustCam;
    m_intakeCamshaft = params.IntakeCam;
    m_exhaustPortFlow = params.ExhaustPortFlow;
    m_intakePortFlow = params.IntakePortFlow;
    m_combustionChamberVolume = params.CombustionChamberVolume;
    m_flipDisplay = params.FlipDisplay;

    memset(m_exhaustSystems, 0, sizeof(ExhaustSystem *) * params.Bank->m_cylinderCount);
    memset(m_intakes, 0, sizeof(Intake *) * params.Bank->m_cylinderCount);
}

void CylinderHead::destroy() {
    if (m_exhaustSystems != nullptr) delete[] m_exhaustSystems;
    if (m_intakes != nullptr) delete[] m_intakes;

    m_exhaustSystems = nullptr;
    m_intakes = nullptr;
}

double CylinderHead::intakeFlowRate(int cylinder) const {
    return m_intakePortFlow->sampleTriangle(
            intakeValveLift(cylinder)) * m_flow;
}

double CylinderHead::exhaustFlowRate(int cylinder) const {
    return m_exhaustPortFlow->sampleTriangle(
            exhaustValveLift(cylinder)) * m_flow;
}

double CylinderHead::intakeValveLift(int cylinder) const {
    return m_intakeCamshaft->valveLift(cylinder);
}

double CylinderHead::exhaustValveLift(int cylinder) const {
    return m_exhaustCamshaft->valveLift(cylinder);
}

void CylinderHead::setAllExhaustSystems(ExhaustSystem *system) {
    for (int i = 0; i < m_bank->m_cylinderCount; ++i) {
        m_exhaustSystems[i] = system;
    }
}

void CylinderHead::setExhaustSystem(int i, ExhaustSystem *system) {
    m_exhaustSystems[i] = system;
}

void CylinderHead::setAllIntakes(Intake *intake) {
    for (int i = 0; i < m_bank->m_cylinderCount; ++i) {
        m_intakes[i] = intake;
    }
}

void CylinderHead::setIntake(int i, Intake *intake) {
    m_intakes[i] = intake;
}
