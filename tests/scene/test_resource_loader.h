/**************************************************************************/
/*  test_resource_loader.h                                                */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef TEST_RESOURCE_LOADER_H
#define TEST_RESOURCE_LOADER_H

#include "core/io/resource_loader.h"
#include "tests/test_macros.h"

namespace TestResourceLoader {

TEST_CASE("[ResourceFormatLoader] Load Resource - Null Hypothesis") {
	Ref<Resource> resource = ResourceLoader::get_singleton()->load("");
	CHECK_FALSE(resource.is_valid());
}

TEST_CASE("[ResourceFormatLoader] Load Resource - Golden Path") {
	// Load sample valid path.
	Ref<Resource> resource = ResourceLoader::get_singleton()->load("res://images/icon.png");
	CHECK(resource.is_valid());
}

TEST_CASE("[ResourceFormatLoader] Load Resource - Malicious Path") {
	// Load resource with intentionally invalid or prohibited path.
	Ref<Resource> resource = ResourceLoader::get_singleton()->load("res://unauthorized_path/trojan_resource.tres");
	CHECK_FALSE(resource.is_valid());
}

TEST_CASE("[ResourceFormatLoader] Load Whitelisted - Null Hypothesis") {
	Dictionary ext_whitelist;
	Dictionary type_whitelist;
	Ref<Resource> resource = ResourceLoader::get_singleton()->load_whitelisted("", ext_whitelist, type_whitelist);
	CHECK_FALSE(resource.is_valid());
}

TEST_CASE("[ResourceFormatLoader] Load Whitelisted - Golden Path") {
	Dictionary ext_whitelist;
	ext_whitelist["res://images"] = true;
	Dictionary type_whitelist;
	type_whitelist["Resource"] = true;
	Ref<Resource> resource = ResourceLoader::get_singleton()->load_whitelisted(
			"res://images/icon.png", ext_whitelist, type_whitelist, "Resource");
	CHECK(resource.is_valid());
}

TEST_CASE("[ResourceFormatLoader] Load Whitelisted - Malicious Path") {
	Dictionary ext_whitelist;
	// No allowed paths in the whitelist.
	Dictionary type_whitelist;
	type_whitelist["Resource"] = true;
	Ref<Resource> resource = ResourceLoader::get_singleton()->load_whitelisted(
			"res://malicious/test_resource.tres", ext_whitelist, type_whitelist, "Resource");
	CHECK_FALSE(resource.is_valid());
}

} //namespace TestResourceLoader
