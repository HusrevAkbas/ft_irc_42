#pragma once

#include <csignal>
#include <signal.h>

extern volatile sig_atomic_t signal_shutdown;

void setup_signals();
