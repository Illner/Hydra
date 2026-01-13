#pragma once

namespace Hydra::Formula::Representation {

    /**
     * Recognition type structure
     * Copy and move methods (default) are allowed!
     */
    struct RecognitionTypeStruct {
    public:
        bool kromC = false;
        bool hornC = false;
        bool antiHornC = false;
    };
}   // namespace Hydra::Formula::Representation
