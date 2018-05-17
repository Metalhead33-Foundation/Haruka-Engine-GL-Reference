#ifndef SHADERPREPROCESSORINPUT_HPP
#define SHADERPREPROCESSORINPUT_HPP
#include "../abstract/FIOSys.hpp"
#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_interface.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>
#include <stdexcept>

namespace boost {
namespace wave {
namespace iteration_context_policies {

	struct FIO {

		static Abstract::sFIOSys fiosys;
		template <typename IterContext>
		class inner {

		public:
			// expose the begin and end iterators for the
			// included file
			template <typename Position>
			static
			void init_iterators(IterContext&iter_ctx,
				Position const &act_pos)
			{
				typedef typename IterContext::iterator_type iterator_type;

				Abstract::sFIO file = fiosys->openRead(iter_ctx.filename);
				if (!file) {
					throw std::runtime_error("Cannot open file for preprocessing!");
				}

				iter_ctx.instring = file->stringize();

				iter_ctx.first = iterator_type(iter_ctx.instring.begin(),
					iter_ctx.instring.end(),
					PositionT(iter_ctx.filename));
				iter_ctx.last = iterator_type();
			}

		private:
			std::string instring;
		};
	};

}   // namespace iteration_context_policies
typedef cpplexer::lex_iterator<
		cpplexer::lex_token<> >
	lex_iterator_type;
typedef context<std::string::iterator,lex_iterator_type,iteration_context_policies::FIO> FioContext;
}   // namespace wave
}   // namespace boost

#endif // SHADERPREPROCESSORINPUT_HPP
