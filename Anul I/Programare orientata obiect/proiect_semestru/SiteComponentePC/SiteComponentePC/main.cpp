#include "utils.h"
#include "RepoMotherboard.h";
#include "RepoCPU.h"
#include "RepoGPU.h"
#include "RepoRAM.h"
#include "Service.h"
#include "UserInterface.h"
#include "TestCPU.h"
#include "TestGPU.h"
#include "TestRAM.h"
#include "TestMotherboard.h"
#include "TestRepoCPU.h"
#include "TestRepoGPU.h"
#include "TestRepoRAM.h"
#include "TestRepoMBD.h"
#include "TestService.h"
#include <iostream>
using namespace std;

int main()
{
    TestCPU::runTests();
    TestGPU::runTests();
    TestMBD::runTests();
    TestRAM::runTests();
    TestRepoCPU::runTests();
    TestRepoGPU::runTests();
    TestRepoRAM::runTests();
    TestRepoMBD::runTests();
    TestService::runTests();
    
    RepoCPU* repoCPU = new RepoCPU("cpus.txt");
    RepoGPU* repoGPU = new RepoGPU("gpui.txt");
    RepoMBD* repoMBD = new RepoMBD("motherboards.txt");
    RepoRAM* repoRAM = new RepoRAM("rami.txt");

    Service* service = new Service(repoCPU, repoGPU, repoMBD, repoRAM);
    UI ui(service);
    ui.runInterface();
}