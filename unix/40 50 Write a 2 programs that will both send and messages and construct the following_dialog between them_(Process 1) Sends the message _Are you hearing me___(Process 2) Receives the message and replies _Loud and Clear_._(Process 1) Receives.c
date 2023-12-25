#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


#define MAX_MESSAGE_SIZE 100
#define MESSAGE_TYPE 1


struct message_buffer {
   long message_type;
   char message_text[MAX_MESSAGE_SIZE];
};


int main() {
   key_t key;
   int msgid;
   struct message_buffer message;


   // Generate unique key
   key = ftok("message_queue", 65);


   // Create a message queue
   msgid = msgget(key, 0666 | IPC_CREAT);


   // Chat between users
   while (1) {
       // User 1 sends a message
       printf("User 1: ");
       fgets(message.message_text, sizeof(message.message_text), stdin);
       message.message_type = MESSAGE_TYPE;
       msgsnd(msgid, &message, sizeof(message), 0);


       // Check for exit command
       if (strncmp(message.message_text, "exit", 4) == 0)
           break;


       // User 2 receives the message from User 1
       msgrcv(msgid, &message, sizeof(message), MESSAGE_TYPE, 0);
       printf("User 2: %s", message.message_text);


       // Check for exit command
       if (strncmp(message.message_text, "exit", 4) == 0)
           break;


       // User 2 sends a message
       printf("User 2: ");
       fgets(message.message_text, sizeof(message.message_text), stdin);
       message.message_type = MESSAGE_TYPE;
       msgsnd(msgid, &message, sizeof(message), 0);


       // Check for exit command
       if (strncmp(message.message_text, "exit", 4) == 0)
           break;


       // User 1 receives the message from User 2
       msgrcv(msgid, &message, sizeof(message), MESSAGE_TYPE, 0);
       printf("User 1: %s", message.message_text);


       // Check for exit command
       if (strncmp(message.message_text, "exit", 4) == 0)
           break;
   }


   // Delete the message queue
   msgctl(msgid, IPC_RMID, NULL);


   return 0;
}