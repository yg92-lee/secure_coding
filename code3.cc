#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "macros.h"

void _sendFile (int clientSocket) {
  char buffer[BUFF_SIZE] = { '\0' };
  bzero(buffer, BUFF_SIZE);

  int readStatus = read(clientSocket, buffer, BUFF_SIZE);
  if (readStatus < 0) {
    fprintf(stderr, "Error: Reading from socket.\n");
    return;
  }

  // Temporary GET handling.
  char fileName[BUFF_SIZE] = { '\0' };
  // int sscanf ( const char * s, const char * format, ...);
  // Reads data from s and stores them according to parameter format into the locations given by the additional argument
  sscanf(buffer, "GET /%s ", fileName);

  // Handle file request.
  FILE* fp = fopen(fileName, "rb");
  if (!fp) {
    fprintf(stderr, "Error: File opening.\n");
    return;
  }

  fprintf(stdout, "Sending: %s\n", fileName);

  char fileChar = 0;
  int i = -1;
  bzero(buffer, BUFF_SIZE);
  while ((fileChar = fgetc(fp)) != EOF) {
    buffer[++i] = fileChar;
  }
  fclose(fp);

  // Temporary header handling - only text/HTML at the moment.
  char header[BUFF_SIZE] = "HTTP/1.1 200 OK\r\n";
  char contentType[BUFF_SIZE] = "Content-Type: text/html; charset=UTF-8\r\n";
  char contentLength[BUFF_SIZE] = { '\0' };
  sprintf(contentLength, "Content-Length: %zu\r\n", strlen(buffer) + 1);

  char response[BUFF_SIZE] = { '\0' };
  strcat(response, header);
  strcat(response, contentType);
  strcat(response, contentLength);
  strcat(response, "\r\n\r\n");

  // There goes the header.
  if (write(clientSocket, response, strlen(response)) < 0) {
    fprintf(stderr, "Error: Sending header.\n");
    return;
  };

  // Now the file.
  if (write(clientSocket, buffer, strlen(buffer) + 1) < 0) {
    fprintf(stderr, "Error: Sending file.\n");
    return;
  }

  fprintf(stdout, "Sent: %s\n\n", fileName);
  fprintf(stdout, "Waiting..\n\n");
}
