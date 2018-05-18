#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}


int main(void)
{
  CURL *curl;
  CURLcode res;
  char *header = "Station-State: Enabled";
  char *header2 = "User-ID-String: test";
  struct curl_slist *headers = NULL;

  static const char *postthis = "testing";
  static const char *pCertFile = "/u/guen/test/LUCCA/test/cert/combined.pem";

  curl = curl_easy_init();
  if(curl) {

    struct string s;
    init_string(&s);
    headers = curl_slist_append(headers, header);
    headers = curl_slist_append(headers, header2);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
    //curl_easy_setopt(curl, CURLOPT_URL, "https://webhook.site/d9647a35-e922-426a-a300-9fdd0eb33249");
    //curl_easy_setopt(curl, CURLOPT_URL, "https://ruby.cecs.pdx.edu:3001");
    curl_easy_setopt(curl, CURLOPT_URL, "http://ptsv2.com/t/xj3ym-1525325338/post");

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
       itself */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));

    /* cert stored PEM coded in file */
    curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");

    /* set cert for client authentication */
    curl_easy_setopt(curl, CURLOPT_SSLCERT, pCertFile);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    printf("\n===================\nResponse Code: %ld\n===================\n", response_code);
    printf("%s\n\n", s.ptr);

    /* always cleanup */
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }
  return 0;
}
