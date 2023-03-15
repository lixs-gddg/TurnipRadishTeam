#include <iostream>
#include <fstream>
#include "interact.h"

bool readUntilOK() {
    char line[1024];
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        //do something
    }
    return false;
}

int main() {
    readUntilOK();
    puts("OK");
    fflush(stdout);
    
    while(Interactor::readFrame()){
        printf("%d\n", Interactor::curFrame);
        int lineSpeed = 3;
        double angleSpeed = 1.5;
        for(int robotId = 0; robotId < 4; robotId++){
            printf("forward %d %d\n", robotId, lineSpeed);
            printf("rotate %d %f\n", robotId, angleSpeed);
        }
        printf("OK\n");
        fflush(stdout);
    }
    // int frameID;
    // while (scanf("%d", &frameID) != EOF) {
    //     readUntilOK();
    //     printf("%d\n", frameID);
    //     int lineSpeed = 3;
    //     double angleSpeed = 1.5;
    //     for(int robotId = 0; robotId < 4; robotId++){
    //         printf("forward %d %d\n", robotId, lineSpeed);
    //         printf("rotate %d %f\n", robotId, angleSpeed);
    //     }
    //     printf("OK\n");
    //     fflush(stdout);
    // }
    return 0;
}
