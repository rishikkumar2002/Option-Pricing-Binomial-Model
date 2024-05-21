#include <filesystem>
#include <iostream>

#include "capture_output.hpp"

int main()
{
    const std::filesystem::path root = PROJECT_ROOT_DIR;

    const std::filesystem::path cmd = root / "build" / "option_pricing_convergence";
    const std::filesystem::path output = root / "convergence_output" / "output.csv";

    capture_output(cmd.string(), output.string());
    return 0;
}