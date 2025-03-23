export module Vigenere;


import <string>;
import <vector>;
import <iostream>;


export std::string to_lower_hardcoded(std::string s_in);
export std::string crypt(std::string& key, std::string& msg);
export std::string decrypt(std::string& key, std::string& msg);


std::string to_lower(std::string& s_in) {
	std::string s_out = s_in;

	for (size_t i = 0; i < s_in.length(); i++) {
		s_out[i] = std::tolower(s_in[i]);
	}
	return s_out;

}

std::string to_lower_hardcoded(std::string s_in) {
	std::string s_out = s_in;

	for (size_t i = 0; i < s_in.length(); i++) {
		s_out[i] = std::tolower(s_in[i]);
	}
	return s_out;

}


std::string crypt(std::string& key, std::string& msg){
	std::string encoded_msg;
	msg = to_lower(msg);
	int aux = 0;
	for (size_t i = 0; i < msg.length(); i++) {
		if (std::isalpha(msg[i])) {
			encoded_msg += ((msg[i] - 'a' + key[i % key.length()] - 'a') % 26 + 'a');
			aux = (i + 1) % key.length();
		}
		else {
			encoded_msg += msg[i]; // Add non-alphabetic characters without change
		}

	}
	return encoded_msg;
}

std::string invert_key(std::string& key) {
	key = to_lower(key);
	std::string anti_key = key;
	for (size_t i = 0; i < key.length(); i++)
	{
		anti_key[i] = -(key[i] - 'a') + 'a';
		if (key[i] != 'a')
		{
			anti_key[i] += 26;
		}
	}
	// std::cout << "antichiave: " << anti_key << std::endl; // debug
	return anti_key;
}

std::string decrypt(std::string& key, std::string& msg) {
	key = to_lower(key);
	msg = to_lower(msg);
	std::string a_key = invert_key(key);
	return crypt(a_key, msg);
}
