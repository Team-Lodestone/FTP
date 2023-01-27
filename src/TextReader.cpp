#include <iostream>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((std::stringstream*) stream) << data << std::endl;
    return size * nmemb;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    std::stringstream out;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "ftp://ftp.example.com/file.txt");
        curl_easy_setopt(curl, CURLOPT_USERNAME, "username");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "password");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << out.str();
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}
