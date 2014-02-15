/* This file is part of the Palabos library.
 *
 * Copyright (C) 2011-2013 FlowKit Sarl
 * Route d'Oron 2
 * 1010 Lausanne, Switzerland
 * E-mail contact: contact@flowkit.com
 *
 * The most recent release of Palabos can be downloaded at 
 * <http://www.palabos.org/>
 *
 * The library Palabos is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * The library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MULTI_PARTICLE_FIELD_2D_H
#define MULTI_PARTICLE_FIELD_2D_H

#include "core/globalDefs.h"
#include "multiBlock/multiBlock2D.h"
#include "particles/particleField2D.h"

namespace plb {

template<class ParticleFieldT>
class MultiParticleField2D : public MultiBlock2D {
public:
    typedef std::map<plint,ParticleFieldT*> BlockMap;
public:
    MultiParticleField2D (
            MultiBlockManagement2D const& multiBlockManagement_,
            CombinedStatistics* combinedStatistics_ );
    MultiParticleField2D(plint nx_, plint ny_);
    MultiParticleField2D(MultiBlock2D const& rhs);
    MultiParticleField2D(MultiBlock2D const& rhs, Box2D subDomain, bool crop);
    ~MultiParticleField2D();
    virtual MultiParticleField2D<ParticleFieldT>* clone() const;
    virtual MultiParticleField2D<ParticleFieldT>* clone(MultiBlockManagement2D const& newManagement) const;
    MultiParticleField2D& operator=(MultiParticleField2D<ParticleFieldT> const& rhs);
    MultiParticleField2D(MultiParticleField2D<ParticleFieldT> const& rhs);
    void swap(MultiParticleField2D<ParticleFieldT>& rhs);
public:
    virtual ParticleFieldT& getComponent(plint iBlock);
    virtual ParticleFieldT const& getComponent(plint iBlock) const;
    virtual plint sizeOfCell() const;
    virtual plint getCellDim() const;
    virtual int getStaticId() const;
    virtual void copyReceive (
                    MultiBlock2D const& fromBlock, Box2D const& fromDomain,
                    Box2D const& toDomain, modif::ModifT whichData=modif::dataStructure );
    std::string getBlockName() const;
    std::vector<std::string> getTypeInfo() const;
    static std::string blockName();
    static std::string basicType();
    static std::string descriptorType();
private:
    void allocateBlocks();
    void deAllocateBlocks();
private:
    BlockMap blocks;
    static const int staticId;
};

}  // namespace plb

#endif  // MULTI_PARTICLE_FIELD_2D_H