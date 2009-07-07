/** 
 * @file lliconctrl.cpp
 * @brief LLIconCtrl base class
 *
 * $LicenseInfo:firstyear=2001&license=viewergpl$
 * 
 * Copyright (c) 2001-2009, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#include "linden_common.h"

#include "lliconctrl.h"

// Linden library includes 

// Project includes
#include "llcontrol.h"
#include "llui.h"
#include "lluictrlfactory.h"
#include "lluiimage.h"

static LLDefaultChildRegistry::Register<LLIconCtrl> r("icon");

LLIconCtrl::Params::Params()
:	image("image_name"),
	color("color"),
	scale_image("scale_image")
{
	tab_stop = false;
	mouse_opaque = false;
}

LLIconCtrl::LLIconCtrl(const LLIconCtrl::Params& p)
:	LLUICtrl(p),
	mColor(p.color()),
	mImagep(p.image)
{
	if (mImagep.notNull())
	{
		LLUICtrl::setValue(mImagep->getName());
	}
}

LLIconCtrl::~LLIconCtrl()
{
	mImagep = NULL;
}


void LLIconCtrl::draw()
{
	if( mImagep.notNull() )
	{
		mImagep->draw(getLocalRect(), mColor.get() );
	}

	LLUICtrl::draw();
}

// virtual
// value might be a string or a UUID
void LLIconCtrl::setValue(const LLSD& value )
{
	LLSD tvalue(value);
	if (value.isString() && LLUUID::validate(value.asString()))
	{
		//RN: support UUIDs masquerading as strings
		tvalue = LLSD(LLUUID(value.asString()));
	}
	LLUICtrl::setValue(tvalue);
	if (tvalue.isUUID())
	{
		mImagep = LLUI::getUIImageByID(tvalue.asUUID());
	}
	else
	{
		mImagep = LLUI::getUIImage(tvalue.asString());
	}
}

std::string LLIconCtrl::getImageName() const
{
	if (getValue().isString())
		return getValue().asString();
	else
		return std::string();
}
