#pragma once

template < bool >
struct CompileTimeError;
template < >
struct CompileTimeError< true >;

#define CYDL_STATIC_CHECK(expr) ( CompileTimeError< (expr) != 0 >() )