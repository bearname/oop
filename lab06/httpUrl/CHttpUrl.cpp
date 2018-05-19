#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url)
{
	ParseUrl(url);
	m_url = url;
}

CHttpUrl::CHttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_domain(VerifyDomain(domain))
	, m_document(VerifyDocument(document))
	, m_protocol(protocol)
{
	m_port = static_cast<unsigned short>(m_protocol);
	SetUrl();
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
	: m_domain(VerifyDomain(domain))
	, m_document(VerifyDocument(document))
	, m_protocol(protocol)
	, m_port(VerifyPortRange(port))
{
	SetUrl();
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetProtocolString() const
{
	if (m_protocol == Protocol::HTTP)
	{
		return "http";
	}

	return "https";
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::SetUrl()
{
	m_url += GetProtocolString() + "://" + m_domain;
	if (m_port != static_cast<unsigned short>(m_protocol))
	{
		m_url += ":" + std::to_string(m_port);
	}

	m_url += (!m_document.empty() ? m_document :  "/" + m_document);
}

void CHttpUrl::ParseUrl(std::string const& url)
{
	ThrowWhenStringEmpty(url, "url can't be empty");

	constexpr char REGULAR_EXPRESSION[] = "^(https?)://([A-Za-z0-9-.]+)(:?([0-9]+))?(/(.*))?$";
	std::regex pattern(REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_match(url, match, pattern))
	{
		throw CUrlParsingError("failed parse url");
	}

	m_protocol = VerifyProtocolString(match[1]);
	m_domain = VerifyDomain(match[2]);
	m_port = ParsePort(m_protocol, match[4]);
	m_document = VerifyDocument(match[6]);
}

Protocol CHttpUrl::VerifyProtocolString(const std::string& protocolStr)
{
	std::string lowerProtocolStr = protocolStr;

	std::transform(lowerProtocolStr.begin(), lowerProtocolStr.end(),
		lowerProtocolStr.begin(), ::tolower);

	if (lowerProtocolStr == "http")
	{
		return Protocol::HTTP;
	}
	else if (lowerProtocolStr == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("unnkonw protocol");
}

std::string CHttpUrl::VerifyDomain(std::string const& domain)
{
	ThrowWhenStringEmpty(domain, "domain can't be empty");

	constexpr char REGULAR_EXPRESSION[] = "^([A-Za-z0-9-.]+)?$";
	std::regex pattern(REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_match(domain, match, pattern))
	{
		throw CUrlParsingError("failed parse domain '" + domain + "'");
	}

	return match[1];
}

std::string CHttpUrl::VerifyDocument(std::string const& document)
{
	std::string result = document;
	if (result.empty() || !result.empty() && result[0] != '/')
	{
		result = "/" + result;
	}

	return result;
}

unsigned short CHttpUrl::VerifyPortRange(unsigned short port)
{
	constexpr unsigned short MIN_NUMBER_PORT = 1;
	constexpr unsigned short MAX_NUMBER_PORT = 65535;

	if (port < MIN_NUMBER_PORT || port > MAX_NUMBER_PORT)
	{
		throw CUrlParsingError("invalid port range " + port);
	}

	return port;
}

constexpr unsigned short DEFAULT_HTTP_PORT = 80;
constexpr unsigned short DEFAULT_HTTPS_PORT = 443;

unsigned short CHttpUrl::ParsePort(const Protocol& protocol, const std::string& portStr)
{
	if (portStr.empty())
	{
		return static_cast<unsigned short>(protocol);
	}

	return VerifyPortRange(static_cast<unsigned short>(stoi(portStr)));
}

void CHttpUrl::ThrowWhenStringEmpty(std::string const& str, std::string const& msg)
{
	if (str.empty())
	{
		throw CUrlParsingError(msg);
	}
}

std::ostream& operator<<(std::ostream& output, CHttpUrl const& httpUrl)
{
	output << "url: '" << httpUrl.GetURL() << "'\n"
		   << "protocol: '" << httpUrl.GetProtocolString() << "'\n"
		   << "port: '" << httpUrl.GetPort() << "'\n"
		   << "domain: '" << httpUrl.GetDomain() << "'\n"
		   << "document: '" << httpUrl.GetDocument() << "'";

	return output;
}
