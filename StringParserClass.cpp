/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace KP_StringParserClass;

//dont forget to initialize member variables
StringParserClass::StringParserClass():pStartTag(0), pEndTag(0), areTagsSet(false) {

}

//call cleanup to release any allocated memory
StringParserClass::~StringParserClass() {
	if (pEndTag) {
		delete pEndTag;
	}
	if (pStartTag) {
		delete pStartTag;
	}
}

//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (!pStart || !pEnd) {
		return ERROR_TAGS_NULL;
	}

	int len = strlen(pStart);
	int lens = strlen(pEnd);

	pStartTag = new char[len + 1];
	pEndTag = new char[lens + 1];

	strncpy(pStartTag, pStart, len);
	strncpy(pEndTag, pEnd, lens);

	areTagsSet = true;

	return 0;

}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector) {

	if (!pStartTag || !pEndTag) {
		return ERROR_TAGS_NULL;
	}
	if (!pDataToSearchThru) {
		return ERROR_DATA_NULL;
	}

	myVector.clear();

	int len = strlen(pDataToSearchThru);
	char *point;
	char *epoint;
	char *point1;
	char *epoint1;
	int i = 0;
	int j = 0;
	char *start;
	std::string save = "";

	while (i < len) {
		if (*(pDataToSearchThru + i) == *pStartTag) {

			point = pDataToSearchThru + i;
			epoint = point + strlen(pStartTag) - 3;
			start = epoint + 1;

			if ((StringParserClass::findTag(pStartTag, point, epoint)) == SUCCESS) {

				j = i;
				while (j < len) {
					if (*(pDataToSearchThru + j) == *pEndTag) {

						point1 = pDataToSearchThru + j;
						epoint1 = point1 + strlen(pEndTag) - 2;

						if ((StringParserClass::findTag(pEndTag, point1, epoint1)) == SUCCESS) {

							save.append(start, strlen(start) - strlen(point1));

							if (save != "") {
								myVector.push_back(save);
							}
							save = "";
							j = len;
						}
					}
					j++;
				}

			}
		}
		i++;
	}

	return 0;
}

void StringParserClass::cleanup() {

}

//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
	if (!pEnd || !pStart) {
		return ERROR_TAGS_NULL;
	}
	if (pEnd == 0) {
		return FAIL;
	}

	if ((strncmp((pStart), pTagToLookFor, strlen(pTagToLookFor) - 2) == 0)) {
		return SUCCESS;
	}

	return FAIL;
}

