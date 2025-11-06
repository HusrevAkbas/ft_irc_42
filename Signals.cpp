#include "Signals.hpp"

volatile sig_atomic_t signal_shutdown = 0; //sig_atomic ensures if program needs to be terminated it will immediately be read before any other operation can happend and signal shut down, volatile ensures flag value isnt cached

static void signalHandler(int sig) {
    (void)sig; //signalHandler needs to have int param to pass it to sa_handler
    //cleanup memory
    signal_shutdown = 1;
    //message? cant use printf
}

static struct sigaction createHandler(void (*handler)(int), int flags) {
    struct sigaction sig;
    sig.sa_handler = handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = flags;
    return sig;
}

void setup_signals() {
    //
    struct sigaction sig = createHandler(signalHandler, 0);
    sigaction(SIGINT, &sig, NULL);
    sigaction(SIGTERM, &sig, NULL);
    sigaction(SIGQUIT, &sig, NULL);
    
    
    //SIGPIPE ?
}
