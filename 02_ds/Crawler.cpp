#include "Crawler.h"

Crawler::Crawler(vector<queue<string>>* lq_vec, 
				 vector<unordered_set<string>>* vs_vec, 
				 const int id, 
				 const int& num_t) {
	this->id = id;
	this->lq_vec = lq_vec;
	this->vs_vec = vs_vec;
	this->ready_flag = false;
	this->num_thread = num_t;
	this->num_crawled = 0;
	this->num_extract = 0;
	this->num_push2LQ = 0;
	for (int i = 0; i < num_t; i++) {
		vector<string> vs;
		this->lq_vecs.push_back(vs);
	}
}

/* set crawler target URL to input string URL */
void Crawler::setURL(string URL) { this->URL = URL; this->ready_flag = true; }

/* return current crawler's target URL */
string Crawler::getURL() { return this->URL; }

/* return crawler's id */
int Crawler::getID() { return this->id; }

/* return ready_flag, defaut = false when crawler was created
   true if crawler has set a target URL, false if crawler has no target URL */
bool Crawler::isReady() { return this->ready_flag; }

/* curl WriteCallback, set buffer size */
size_t Crawler::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/* get all html contain from page rerturn page content string */
string Crawler::getContents(string URL)
{
	CURL* curl;															/* null pointer ready for a session */
	CURLcode res;														/* to catch a CURLcode error code */
	string read_buffer;

	curl = curl_easy_init();											/* Start a libcurl easy session */
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());				/* pass url pointer */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);	/* pass a pointer to CALLBACK */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);		/* pass a write buffer */
		res = curl_easy_perform(curl);									/* reads/writes available data from easy_handle*/
		curl_easy_cleanup(curl);										/* always clean up easy session */
		return read_buffer;
	}
}

/* extrsct domains from URL */
string Crawler::getDomain(string URL)
{
	int index, length;
	index = URL.find(".com");
	length = 4;
	if (index == -1) { index = URL.find(".org"); length = 4; }
	if (index == -1) { index = URL.find(".net"); length = 4; }
	if (index == -1) { index = URL.find(".int"); length = 4; }
	if (index == -1) { index = URL.find(".edu"); length = 4; }
	if (index == -1) { index = URL.find(".ac"); length = 3; }
	string domain = URL.substr(0, index + length);
	return domain;
}

/* relative path */
bool Crawler::isRelative(const string& link)
{
	if (link.substr(0, 4) != "http")
		return true;
	else
		return false;
}

/* extrach all hyperlinks from html page contain, file parseing availiable
   push links into crawlers local links vectors, maximum 3000 links per page */
void Crawler::getLinks()
{
	num_crawled++;		/* increase when crawler start executing crawling a url*/
	string contents = getContents(URL);
	//cout << " contents: " << endl << contents << endl;
	int t = 3000;
	int next = 0;
	while (t--)
	{
		/* parse href attribute , get link start pos and end pos*/
		int i = contents.find("href", next), end = contents.find(">", i);
		if (i == -1 || end == -1)
			break;
		int r = 0;
		for (int j = i; j < end; j++) {
			if (contents[j] == '"' && r == 1) {
				end = j;
				break;
			}
			if (contents[j] == '"')
				r++;
		}
		next = end;
		/* extract link string */
		string link;
		if (contents[i + 5] == '"' || contents[i + 5] == '\'')
			link = contents.substr(i + 6, end - i - 6);
		else
			link = contents.substr(i + 5, end - i - 5);

		/* skip the internal links which are starting with '#'
		   parse relative path and transform to abs url */
		if (link[0] == '#' || link.find('<') != string::npos) continue;
		int chunk = addASCValues(link);
		if (isRelative(link))
		{
			if (link[0] == '/') {
				link.insert(0, getDomain(URL));
			}
			else {
				int j = 0, val = 0;
				for (j = 7; j < URL.length(); j++) {
					if (URL[j] == '/' && URL[j - 1] != '/') val = j;
				}
				link.insert(0, string(URL.substr(0, val + 1)));
			}
		}
		num_extract++;

		/* push links to crawler's links vector
		   Restrict the scope of the search under: URL */
		if (getDomain(link) == getDomain(URL) && link != URL && link != getDomain(URL)) {
			lq_vecs.at(chunk).push_back(link);
		}
	}
}

/* push links of extract by crawler into link queue by chunk id */
void Crawler::pushLinks() {
	for (int id = 0; id < num_thread; id++) {
		vector<string>* lq = &lq_vecs.at(id);
		int size_lq = lq->size();
		for (int j = 0; j < size_lq; j++) {
			string link = lq->at(j);
			if (inVisited(link, id)) {				/* if link belong to this chunk and has visited */
				continue;							/* continue to next link */
			}
			else {
				vs_vec->at(id).insert(link);		/* add link to visited set */
				lq_vec->at(id).push(link);			/* add link to link queue */
				num_push2LQ++;
			}
		}
		lq->clear();
	}
	ready_flag = false;
}

/* add up ascii value of input string tkn then mod by number of thread */
int Crawler::addASCValues(const string& s) {
	int sum = 0;
	for (char c : s)
		sum += c;
	return sum % num_thread;
}

/* check link is already exist in visited set or not */
bool Crawler::inVisited(const string& link, const int& id) {
	return vs_vec->at(id).find(link) != vs_vec->at(id).end();
}

void Crawler::printStatics() {
	cout << "----------------------------" << endl;
	cout << " crawler: " << id << endl;
	cout << " crawled: " << num_crawled << endl;
	cout << " extract: " << num_extract << endl;
	cout << " push2LQ: " << num_push2LQ << endl;
	cout << "----------------------------" << endl;
}

Crawler::~Crawler() {}