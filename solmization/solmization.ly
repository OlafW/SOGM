\version "2.16.0" 

\score { 
	<< 
	\new Staff { 
		\new Voice { 
			\clef "bass" 
			b4 b4 f4 c'4 g,4 g4 d'4 f'4 c'4 
		}
		\addlyrics { 
			ut que -- ant lax -- is re -- son -- a -- re
		}
	}
	>> 

	\layout { 
		\context { 
		\Staff
			\remove Bar_engraver
			\remove Time_signature_engraver 
		}
	}
}
