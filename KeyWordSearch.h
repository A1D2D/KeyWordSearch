#ifndef GIT_CL_KEYWORD_SEARCH_KEYWORD_SEARCH_H
#define GIT_CL_KEYWORD_SEARCH_KEYWORD_SEARCH_H

#include <vector>
#include <regex>

namespace StringUtils {
   std::string escapeRegex(const std::string& keyword) {
      static const std::regex specialChars{R"([-[\]{}()*+?.,\^$|#\s])"};
      return std::regex_replace(keyword, specialChars, R"(\$&)");
   }

   class KeyWordSearch {
   public:
      struct MatchDetail {
         std::string keyword;
         size_t position;
         size_t id;
      };

      struct SearchKeyword {
         std::string keyWord;
         bool caseSensitive = true;
         bool lineStart = false;
      };

      KeyWordSearch() = default;

      ~KeyWordSearch() = default;

      std::vector<MatchDetail> findKeywords(const std::string& text) const {
         std::vector<MatchDetail> matches;
         std::vector<SearchKeyword> tempKeyWords = keyWords;
         std::vector<size_t> sortedIDs = sortKeywordsByLength(tempKeyWords);
         std::regex pattern(createRegexPattern(tempKeyWords), std::regex::multiline);//2048

         auto wordsBegin = std::sregex_iterator(text.begin(), text.end(), pattern);
         auto wordsEnd = std::sregex_iterator();
         for (std::sregex_iterator it = wordsBegin; it != wordsEnd; ++it) {
            const std::smatch& match = *it;
            for (size_t j = 1; j < match.size(); ++j) {
               if (match[j].matched) {
                  matches.push_back({match.str(j), static_cast<size_t>(match.position(j)), sortedIDs[j-1]});
               }
            }
         }
         return matches;
      }

      std::vector<SearchKeyword> keyWords;

      void addKeyWord(const std::string& keyWord, const bool& caseSensitive, const bool& lineStart) {
         keyWords.push_back({keyWord,caseSensitive,lineStart});
      }

      void addKeyWord(const std::string &keyWord) {
         keyWords.push_back({keyWord,true,false});
      }

      void removeKeyWord(const std::string &keyWord) {
         keyWords.erase(
            std::remove_if(keyWords.begin(), keyWords.end(),
               [&keyWord](const SearchKeyword& keyword) {
                  return keyword.keyWord == keyWord;
               }),
            keyWords.end()
         );
      }

   private:
      static std::vector<size_t> sortKeywordsByLength(std::vector<SearchKeyword>& keywords) {
         std::vector<std::pair<size_t , SearchKeyword>> pairs(keywords.size());
         for (int i = 0; i < keywords.size(); ++i) {
            pairs[i] = std::make_pair(i, keywords[i]);
         }

         std::sort(pairs.begin(), pairs.end(), [](const std::pair<size_t , SearchKeyword>& a, const std::pair<size_t , SearchKeyword>& b) {
            return a.second.keyWord.size() > b.second.keyWord.size();
         });

         for (int pID = 0; pID < keywords.size(); ++pID) {
            keywords[pID] = pairs[pID].second;
         }

         std::vector<size_t> sortedIDs(keywords.size());
         for (int pID = 0; pID < keywords.size(); ++pID) {
            sortedIDs[pID] = pairs[pID].first;
         }
         return sortedIDs;
      }

      static std::string createRegexPattern(const std::vector<SearchKeyword>& keywords) {
         std::string pattern;
         for (size_t i = 0; i < keywords.size(); ++i) {
            if (i != 0) {
               pattern += "|";
            }
            pattern += "(";
            if (keywords[i].lineStart) {
               pattern += "^[\\t| ]*";
            }

            if (keywords[i].caseSensitive) {
               pattern += escapeRegex(keywords[i].keyWord);
            } else {
               std::string caseless_pattern;
               for (char c : keywords[i].keyWord) {
                  caseless_pattern += "[" + std::string(1, (char)std::toupper(c)) + "|" + std::string(1, (char)std::tolower(c)) + "]";
               }
               pattern += caseless_pattern;
            }
            pattern += ")";
         }
         return pattern;
      }
   };
}

#endif //GIT_CL_KEYWORD_SEARCH_KEYWORD_SEARCH_H
