#pragma once
#include <string>

enum message_status
{
    error_read_file,
    program_error,
    okay,
    end_game,
    none
};

struct game_message
{
    game_message(message_status status, std::string text, bool success) : status(status),message_text(text),success(success) {};
    message_status status;
    std::string message_text;
    bool success;
};

#define SUCCESS_MESSAGE game_message(okay,"",true)