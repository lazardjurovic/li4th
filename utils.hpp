#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> tokenize(std::string input){
        
        std::istringstream iss(input);
        
        std::vector<std::string> tokens;
        std::string token;

        while (iss >> token) {
            tokens.push_back(token);
        }   

        return tokens;
}

bool check_number(std::string str) {

   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;

}