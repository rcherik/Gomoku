/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_path.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 11:47:03 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <mach-o/dyld.h>

#ifdef __linux__
std::string	getRealPath(void)
{
	char		tmp[32];
	char		buf[1024];
	int			bytes;
	std::string	s;
	
	sprintf(tmp, "/proc/%d/exe", getpid());
	bytes = readlink(tmp, buf, 1024);
	bytes = bytes > 1023 ? 1203 : bytes;
	if (bytes >= 0)
		buf[bytes] = 0;
	s = std::string(buf);
	s.erase(s.begin() + s.find_last_of("/"), s.end());
	s += std::string("/");
	return (s);
}
#endif

#ifdef __APPLE__
std::string	getRealPath(void)
{
	char		buf[1024];
	uint32_t		size;
	std::string	s;

	size = 1024;
	if (_NSGetExecutablePath(buf, &size) != 0)
		return ("");
	buf[size - 1] = 0;
	s = std::string(buf);
	s.erase(s.begin() + s.find_last_of("/"), s.end());
	s += std::string("/");
	return (s);
}
#endif
