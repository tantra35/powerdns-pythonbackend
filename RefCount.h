
/*
 * $Id: RefCount.h,v 1.11 2007/04/25 11:30:15 adrian Exp $
 *
 * DEBUG: none          Refcount allocator
 * AUTHOR:  Robert Collins
 *
 * SQUID Web Proxy Cache          http://www.squid-cache.org/
 * ----------------------------------------------------------
 *
 *  Squid is the result of efforts by numerous individuals from
 *  the Internet community; see the CONTRIBUTORS file for full
 *  details.   Many organizations have provided support for Squid's
 *  development; see the SPONSORS file for full details.  Squid is
 *  Copyrighted (C) 2001 by the Regents of the University of
 *  California; see the COPYRIGHT file for full details.  Squid
 *  incorporates software developed and/or copyrighted by other
 *  sources; see the CREDITS file for full details.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#ifndef _SQUID_REFCOUNT_H_
#define _SQUID_REFCOUNT_H_

template <class C>

class RefCount
{

public:
    RefCount () : p_ (NULL)
    {
    }

    RefCount (C *p) : p_(p)
    {
		}

    ~RefCount()
    {
        dereference();
    }

    RefCount (const RefCount &p) : p_(p.p_)
    {
        reference (p);
    }

    RefCount& operator = (const RefCount& p)
    {
        // DO NOT CHANGE THE ORDER HERE!!!
        // This preserves semantics on self assignment
        C *newP_ = p.p_;
        reference(p);
        dereference(newP_);
        return *this;
    }

		bool operator !() const { return !p_; }
		
		operator C* () {return p_;}
		
		C const ** operator& () const {return &p_; }
		
		C ** operator& () {return const_cast<C **>(&p_); }

    C const * operator-> () const {return p_; }

    C * operator-> () {return const_cast<C *>(p_); }

    C const & operator * () const {return *p_; }

    C & operator * () {return *const_cast<C *>(p_); }

    C * getRaw() const{return p_; }

    bool operator == (const RefCount& p) const
    {
        return p.p_ == p_;
    }

    bool operator != (const RefCount &p) const
    {
        return p.p_ != p_;
    }

private:
    void dereference(C *newP = NULL)
    {
        /* Setting p_ first is important:
        * we may be freed ourselves as a result of
        * delete p_;
        */
        C (*tempP_) (p_);
        p_ = newP;

        if (tempP_)
            Py_DECREF(tempP_);
    }

    void reference (const RefCount& p)
    {
        if (p.p_)
           Py_INCREF(p.p_);
    }

    C *p_;

};

#endif /* _SQUID_REFCOUNT_H_ */
