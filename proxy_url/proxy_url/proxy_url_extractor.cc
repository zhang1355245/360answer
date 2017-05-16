
#include "proxy_url_extractor.h"
#include <fstream>
#include <vector>
#include "tokener.h"

namespace qh
{

    namespace {

        template< class _StringVector, 
        class StringType,
        class _DelimType> 
            inline void StringSplit(  
            const StringType& str, 
            const _DelimType& delims, 
            unsigned int maxSplits, 
            _StringVector& ret)
        {
            unsigned int numSplits = 0;

            // Use STL methods
            size_t start, pos;
            start = 0;

            do
            {
                pos = str.find_first_of( delims, start );

                if ( pos == start )
                {
                    ret.push_back(StringType());
                    start = pos + 1;
                }
                else if ( pos == StringType::npos || ( maxSplits && numSplits + 1== maxSplits ) )
                {
                    // Copy the rest of the string
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, str.size() - start);
                    break;
                }
                else
                {
                    // Copy up to delimiter
                    //ret.push_back( str.substr( start, pos - start ) );
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, pos - start);
                    start = pos + 1;
                }

                ++numSplits;

            }
            while ( pos != StringType::npos );
        }
    }

    ProxyURLExtractor::ProxyURLExtractor()
    {
    }

    bool ProxyURLExtractor::Initialize( const std::string& param_keys_path )
    {
        std::ifstream ifs;
        ifs.open(param_keys_path.data(), std::fstream::in);
        typedef std::vector<std::string> stringvector;
        stringvector keysvect;
        
        while (!ifs.eof()) {
            std::string line;
            getline(ifs, line);
            if (ifs.fail() && !ifs.eof()) {
                fprintf(stderr, "SubUrlExtractor::LoadParamKeysFile readfile_error=[%s] error!!", param_keys_path.data());
                ifs.close();
                return false;
            }
            if (line.empty()) continue;

            keysvect.clear();
            StringSplit(line, ",", static_cast<unsigned int>(-1), keysvect);
            assert(keysvect.size() >= 1);
            keys_set_.insert(keysvect.begin(), keysvect.end());
            keys_set_.erase("");
        }

        ifs.close();

        return true;
    }

    std::string ProxyURLExtractor::Extract( const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys_set_, raw_url, sub_url);
        return sub_url;
    }

	void ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url, std::string& sub_url )
    {
#if 1
        // TODO 请面试者在这里添加自己的代码实现以完成所需功能 这是我的答案
		// 时间复杂度：n为set的大小，m为url中等于符号‘=’的数量，l为URL字符串的长度 O（n*m+l）
		// 空间复杂度： O（2*l） l为URL字符串的长度 因为token变量维护的数据成员为一个完整的字符串，和一个可变的当前字符串。
		// 内存泄露：
		Tokener token(raw_url);
		token.skipTo('?');
		token.next(); //skip one char : '?' 
		std::string key;
		while (!token.isEnd()) {
			key = token.nextString('=');
			size_t j=-1;
			for (size_t i=0; i < key.size(); ++i)
			{
				if (key[i] == '?' || key[i] == '&')
				{
					j = i; // 判断第一个关键字。
				}
			}
			key = key.substr(j + 1);
			if (keys.find(key) != keys.end()) {
				const char* curpos = token.getCurReadPos();
				int nreadable = token.getReadableSize();

				/**
				* case 1:
				*  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
				*  sub_url="http://hnujug.com/"
				*/
				sub_url = token.nextString('&');

				if (sub_url.empty() && nreadable > 0) {
					/**
					* case 2:
					* raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
					* sub_url="http://hnujug.com/"
					*/
					assert(curpos);
					sub_url.assign(curpos, nreadable);
					if (*curpos == '&')
					{
						sub_url = "";  // 判断最后一位是指定关键字的情况。
					}
				}
			}
			if (token.skipTo('&') == '\0') {
				break;  // 判断最后的部分
			}
			token.next();//skip one char : '&'
		}


#else
        //这是一份参考实现，但在特殊情况下工作不能符合预期
        Tokener token(raw_url);
        token.skipTo('?');
        token.next(); //skip one char : '?' 
        std::string key;
        while (!token.isEnd()) {
            key = token.nextString('=');
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();

                /**
                * case 1: 
                *  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
                *  sub_url="http://hnujug.com/"
                */
                sub_url = token.nextString('&');

                if (sub_url.empty() && nreadable > 0) {
                    /**
                    * case 2: 
                    * raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
                    * sub_url="http://hnujug.com/"
                    */
                    assert(curpos);
                    sub_url.assign(curpos, nreadable);
                }
            }
            token.skipTo('&');
            token.next();//skip one char : '&'
        }
#endif
    }

    std::string ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys, raw_url, sub_url);
        return sub_url;
    }
}

