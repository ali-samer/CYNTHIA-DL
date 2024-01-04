#pragma once

CYDL_BEGIN_LIB_NAMESPACE

		CYDL_BEGIN_LIB_DETAILS_NAMESPACE

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-conversion"

		template < class T,
			template < typename > class AllocPolicy = CYDL_VPOLICIES::MallocCreator
		> class CYDL_TEMPLATE_DEFAULT_CFLAG MemoryPool CYDL_FINAL
		{
		public:
			CYDL_FORCE_INLINE MemoryPool ( CYDL_SIZET sizeParam = CYDL_MEMORY_POOL_SIZE )
			{
				expandTheFreeList( sizeParam );
			}
			~MemoryPool ( )
			{
				MemoryPool< T >* nextPtr;
				for ( nextPtr = next ; nextPtr != NULL ; nextPtr = next )
				{
					next = next->next;
					delete[] nextPtr;
				}
			}

			CYDL_STRONG_INLINE void* alloc ( CYDL_SIZET sizeParam ) CYDL_NOEXCEPT
			{
				if ( !next )
					expandTheFreeList( );

				MemoryPool< T >* head = next;
				next = head->next;

				return head;
			}
			CYDL_STRONG_INLINE void free ( void* someElement ) CYDL_NOEXCEPT
			{
				MemoryPool< T >* head = static_cast< MemoryPool< T >* >(someElement);

				head->next = next;
				next = head;
			}

		private:
			MemoryPool< T >* next;
			void expandTheFreeList ( CYDL_SIZET sizeParam = CYDL_MEMORY_POOL_EXPANSION_SIZE )
			{
				CYDL_SIZET size = ( sizeof( T ) > sizeof( MemoryPool< T >* ) ) ?
				                  sizeof( T ) : sizeof( MemoryPool< T >* );

				MemoryPool< T >* runner = static_cast< MemoryPool< T >* >( AllocPolicy< CYDL_INT8 >::Create(size) );

				next = runner;
				for( CYDL_SIZET i = 0; i < sizeParam; i++)
				{
					runner->next = static_cast< MemoryPool< T >* >( AllocPolicy< CYDL_INT8 >::Create(size) );
					runner = runner->next;
				}
				runner->next = 0;
			}
		};

#pragma clang diagnostic pop

		CYDL_END_LIB_DETAILS_NAMESPACE

CYDL_END_LIB_NAMESPACE